
#ifndef TEST_NAIVE_FUNCTION_H
#define TEST_NAIVE_FUNCTION_H

#include <cassert>

#include <memory>

template<typename>
class naive_function;

template<typename ReturnValue, typename ... Args>
class naive_function<ReturnValue(Args...)> {
public:
	// operator= goes here
	template<typename T>
	naive_function& operator=(T t) {
		std::cout << "trace: called operator= :" << typeid(T).name() << std::endl;
		callable_ = std::make_unique<CallableT<T>>(t);
		return *this;
	}

	// operator() goes here
	ReturnValue operator()(Args... args) const {
		assert(callable_);
		return callable_->Invoke(args...);
	}

private:
	class ICallable {
	public:
		virtual ~ICallable() = default;
		virtual ReturnValue Invoke(Args...) = 0;
	};

	template<typename T>
	class CallableT : public ICallable {
	public:
		CallableT(const T& t) : t_(t) {}
		~CallableT() override = default;

		ReturnValue Invoke(Args... args) override {
			return t_(args...);
		}

	private:
		T t_;
	};

	std::unique_ptr<ICallable> callable_;
};

#endif
