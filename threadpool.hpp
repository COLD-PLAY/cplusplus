
#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <condition_variable>
#include <thread>
#include <functional>
#include <stdexcept>

namespace std {
#define THREADPOOL_MAX_NUM 16
// #define THREADPOOL_AUTO_GROW

// �̳߳أ������ύ��κ��� �� lambda ��������ִ�У����Ի�ȡִ�з���ֵ
// ��ֱ��֧�����Ա������֧���ྲ̬��Ա������ȫ�ֺ���
class threadpool {
private:
    using Task = function<void()>; // ������������
    vector<thread> pool_; // �̳߳�
    queue<Task> tasks_; // �������
    mutex lock_; // ͬ����
    condition_variable task_cv_; // ��������
    atomic<bool> run_{ true }; // �̳߳��Ƿ�ִ�У�ԭ�ӱ���
    atomic<int> idlThrNum_{ 0 }; // �����߳�����

public:
    inline threadpool(unsigned short size = 4) { addThread(size); }
    inline ~threadpool() {
        run_ = false;
        task_cv_.notify_all(); // ���������߳�ִ��
        for (auto& thread : pool_) {
            // thread.detach(); // ���̡߳���������
            if (thread.joinable())
                thread.join(); // �ȴ����������ǰ�����߳�һ����ִ����
        }
    }

public:
    // �ύһ������
    // ����.get() ��ȡ����ֵ��ȴ�����ִ���꣬��ȡ����ֵ
    // �����ַ�������ʵ�ֵ������Ա�������������this ָ�����bind ����
    // 1. ʹ�� bind: .commit(std::bind(&Dog::sayHello, &dog));
    // 2. ʹ�� mem_fn: .commit(std::mem_fn(&Dog::sayHello), this);
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> future<decltype(f(args...))> {
        if (!run_)
            throw runtime_error("commit on ThreadPool is stopped.");

        using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type������f�ķ�������
        auto task = make_shared<packaged_task<RetType()>>(
            bind(forward<F>(f), forward<Args>(args)...)
            ); // ���������ڼ���������
        future<RetType> future = task->get_future();
        {
            lock_guard<mutex> lock{ lock_ }; // �Ե�ǰ��������� lock_guard �� mutex �� stack ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()
            tasks_.emplace([task]() { // push(Task{...}) �ŵ����к���
                (*task)();
                });
        }
#ifndef THREADPOOL_AUTO_GROW
        if (idlThrNum_ < 1 && pool_.size() < THREADPOOL_MAX_NUM)
            addThread(1);
#endif // !THREADPOOL_AUTO_GROW
        task_cv_.notify_one(); // ����һ���߳�ִ��

        return future;
    }

    // �����߳�����
    int idlCount() { return idlThrNum_; }
    // �߳�����
    int thrCount() { return pool_.size(); }

#ifndef THREADPOOL_AUTO_GROW
private:
#endif // !THREADPOOL_AUTO_GROW
    // ���ָ���������߳�
    void addThread(unsigned short size) {
        for (; pool_.size() < THREADPOOL_MAX_NUM && size > 0; --size) {
            pool_.emplace_back([this] {
                while (run_) {
                    Task task;
                    {
                        // unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
                        unique_lock<mutex> lock{ lock_ };
                        task_cv_.wait(lock, [this] {
                            return !run_ || !tasks_.empty();
                            }); // wait ֱ���� task
                        if (!run_ && tasks_.empty())
                            return;
                        task = move(tasks_.front()); // ���Ƚ��ȳ��Ӷ�����ȡһ�� task
                        tasks_.pop();
                    }
                    --idlThrNum_;
                    task(); // ִ������
                    ++idlThrNum_;
                }
                });
            ++idlThrNum_;
        }
    }
};

}

#endif
