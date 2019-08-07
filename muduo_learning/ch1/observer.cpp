#include <iostream>
#include <memory>
#include <vector>

class Observer;
class Object {
public:
    Object() = default;
    Object(int64_t value) : _value(value), _observers() {}
    Object(const Object& other) = default;
    ~Object() = default;

    Object& operator=(const Object& rhs) = default;

    bool attach(Observer* observer);
    void unattach(Observer* observer);
    void update(int64_t value);
    int64_t value() const;
    int32_t observer_size() const;

private:
    void _notify();
    
    int64_t _value;
    std::vector<Observer*> _observers;
};

class Observer {
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
    obj->attach(this);
}

Observer::~Observer() {
    _obj->unattach(this);
}

bool Object::attach(Observer* observer) {
    if (observer == nullptr) {
        std::cout << "err args: observer[null]" << std::endl;
        return false;
    }
    std::cout << "attach observer:" << observer << std::endl;
    _observers.push_back(observer);
    return true;
}

void Object::unattach(Observer* observer) {
    if (observer == nullptr) {
        std::cout << "err args: observer[null]" << std::endl;
        return;
    }
    auto it = _observers.begin();
    while (it != _observers.end()) {
        if (*it == observer) {
            std::cout << "unattach observer:" << observer << std::endl;
            it = _observers.erase(it);
        } else {
            ++it;
        }
    }
}

void Object::update(int64_t value) {
    _value = value;
    _notify();
}

int64_t Object::value() const {
    return _value;
}

int32_t Object::observer_size() const {
    return _observers.size();
}

void Object::_notify() {
    for (auto observer : _observers) {
        observer->update(_value);
    }
}
/***************************************************************/

int main(int argc, char** args) {
    Object obj(2);
    Observer obs1(&obj);
    {
        Observer obs2(&obj);

        std::cout << "obs1.observe():" << obs1.observe() << std::endl;
        std::cout << "obs2.observe():" << obs2.observe() << std::endl;
        std::cout << "obj has " << obj.observer_size() << " observer" << std::endl;
    }

    obj.update(3);

    std::cout << "obs1.observe():" << obs1.observe() << std::endl;
    std::cout << "obj has " << obj.observer_size() << " observer" << std::endl;

    return 0;
}
