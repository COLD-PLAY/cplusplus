
#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include <atomic>
#include <future>
#include <queue>
#include <functional>
#include <condition_variable>

using namespace std;

namespace std {
#define MAX_THREAD_NUM 16

class mythreadpool {
private:
    using Task = function<void()>;
    atomic<bool> _stop;
    atomic<int> _idlThrNum{ 0 };
    vector<thread> _pool;
    queue<Task> _tasks;
    mutex _lock; // 同步锁
    condition_variable _thread_cv;

public:
    mythreadpool(int size = 4) {
        addThread(size);
    }
    ~mythreadpool() {
        _stop = true;
        _thread_cv.notify_all();
        for (auto& thread : _pool) {
            if (thread.joinable())
                thread.join();
        }
    }

    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> decltype(f(args...)) {
        if (_stop)
            throw runtime_error("commit error, threadpool has stoped.");
        using RetType = decltype(f(args...));

        auto task = make_shared<packaged_task<RetType()>>(
            bind(forward<F>(f), forward<Args>(args)...)
        );
        future<RetType> future = task->get_future();
        {
            lock_guard<mutex> lock{ _lock };
            _tasks.emplace([task]() {
                (*task)();
            });
        }

        if (_idlThrNum < 1 && _pool.size() < MAX_THREAD_NUM)
            addThread(1);
        _thread_cv.notify_one(); // 唤醒一个线程
        
        return future;
    }

    void addThread(int size) {
        for (; size > 0 && _idlThrNum < MAX_THREAD_NUM; --size) {
            _pool.emplace_back([this] {
                while (!_stop) {
                    Task task;
                    {
                        unique_lock<mutex> lock{ _lock };
                        _thread_cv.wait(lock, [this] {
                            return _stop || !_tasks.empty();
                            });
                        if (_stop && _tasks.empty())
                            return;
                        task = move(_tasks.front());
                        _tasks.pop();
                    }
                    --_idlThrNum;
                    task();
                    ++_idlThrNum;
                }
                });
            ++_idlThrNum;
        }
    }

    int idlThrCount() { return _idlThrNum; }
    int thrCount() { return _pool.size(); }
};
}