#ifndef L_ONEGET_PTR_H
#define L_ONEGET_PTR_H

template<typename T, typename R, typename ...Args>
R* safe_call_pfunction(T *obj, R*(T::*function)(Args...), Args... args) {
    if (obj == nullptr) return nullptr;
    return ((*obj).*function)(args...);
}

template<typename T, typename R, typename ...Args>
R* safe_call_pfunction(T *obj, R default_value, R*(T::*function)(Args...), Args... args) {
    if (obj == nullptr) return default_value;
    return ((*obj).*function)(args...);
}

template<typename T>
struct oneget_ptr {
    oneget_ptr() {}
    oneget_ptr(T* data) : _data(data) {}

    oneget_ptr(const oneget_ptr&) = delete;
    oneget_ptr(const oneget_ptr&&) = delete;

    oneget_ptr& operator=(const oneget_ptr&) = delete;
    oneget_ptr& operator=(const oneget_ptr&&) = delete;

    void operator=(T* data) {
        _data = data;
    }

    void set(T* data) {
        *this = data;
    }
    T* get() {
        auto temp = _data;
        _data = nullptr;
        return temp;
    }
    ~oneget_ptr(){
        delete _data;
    }
private:
    T* _data = nullptr;
};

#endif // L_ONEGET_PTR_H
