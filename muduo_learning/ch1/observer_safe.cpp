#include <iostream>
#include <memory>
#include <vector>
#include "../util.h"

class Observer;
class Object {
public:
    Object() = default;
    Object(int64_t value) : 
            _value(value), _observers(), _mutex() {}
    Object(const Object& other) = default;
    ~Object() = default;

    Object& operator=(const Object& rhs) = default;

    void attach(std::weak_ptr<Observer> observer);
    // void unattach(Observer* observer);
    void update(int64_t value);
    int64_t value() const;
    int32_t observer_size() const;

private:
    int64_t _value;
    mutable MutexLock _mutex;
    std::vector<std::weak_ptr<Observer>> _observers;
};

class Observer : public std::enable_shared_from_this<Observer> {
public:
    Observer(Object* obj);
    ~Observer();

    int64_t observe() {
        return _value;
    }
    void update(int64_t value) {
        _value = value;
    }

private:
    Object* _obj;
    int64_t _value;
};

/***************************************************************/

Observer::Observer(Object* obj) : 
        _obj(obj), _value(obj->value()) {
    obj->attach(shared_from_this());
}

Observer::~Observer() {}

void Object::attach(std::weak_ptr<Observer> observer) {
    MutexLockGuard lock_guard(_mutex);
    _observers.push_back(observer);
}

void Object::update(int64_t value) {
    MutexLockGuard lock_guard(_mutex);
    _value = value;
    auto it = _observers.begin();
    while (it != _observers.end()) {
        std::shared_ptr<Observer> obs(*it); 
        if (obs) {
            obs->update(value);
            ++it;
        } else {
            // convert to shared_ptr failed, indicate 
            // that weak_ptr point to nowhere
            it = _observers.erase(it);
        }
    }
}

int64_t Object::value() const {
    MutexLockGuard lock_guard(_mutex);
    return _value;
}

int32_t Object::observer_size() const {
    MutexLockGuard lock_guard(_mutex);
    return _observers.size();
}

/***************************************************************/

int main(int argc, char** args) {
    std::shared_ptr<Object> obj(new Object(2));
    std::cout << "p1" << std::endl;
    std::shared_ptr<Observer> obs1(new Observer(obj.get()));
    std::cout << "p2" << std::endl;
    {
        std::shared_ptr<Observer> obs2(new Observer(obj.get()));
        std::cout << "obs1.observe():" << obs1->observe() << std::endl;
        std::cout << "p3" << std::endl;
        std::cout << "obs2.observe():" << obs2->observe() << std::endl;
        std::cout << "p4" << std::endl;
        std::cout << "obj has " << obj->observer_size() << " observer" << std::endl;
    }

    std::cout << "p5" << std::endl;
    obj->update(3);

    std::cout << "obs1.observe():" << obs1->observe() << std::endl;
    std::cout << "obj has " << obj->observer_size() << " observer" << std::endl;

    return 0;
}
