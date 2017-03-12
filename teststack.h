#ifndef TESTSTACK_H
#define TESTSTACK_H

template<typename T>
struct Node_
{
    T val;
    Node_* next;
};

template<typename T, typename Alloc = std::allocator<T> >
class TestStack
{
    typedef Node_<T> Node;
    typedef typename Alloc::template rebind<Node>::other allocator;


public:
    TestStack():head(nullptr) {}
    ~TestStack() {clear();}

    bool empty() {return head == nullptr;}
    void push(const T& val);
    T pop();
    void clear();


private:
    Node* head;
    allocator alloc;
};

template<typename T, typename Alloc>
void TestStack<T, Alloc>::push(const T &val)
{
    Node* new_place = alloc.allocate(1);
    alloc.construct(new_place, Node());

    new_place->val = val;
    new_place->next = head;
    head = new_place;
}

template<typename T, typename Alloc>
T TestStack<T, Alloc>::pop()
{
    //std::cout << "pop" << std::endl;
    T ret = head->val;

    Node* tmp = head;
    head = head->next;
    alloc.destroy(tmp);
    alloc.deallocate(tmp, 1);

    return ret;
}

template<typename T, typename Alloc>
void TestStack<T, Alloc>::clear()
{
    Node* tmp = head;
    while(tmp) {
        Node* next_p = tmp->next;
        alloc.destroy(tmp);
        alloc.deallocate(tmp, 1);
        tmp = next_p;
    }
    head = nullptr;
}

#endif // TESTSTACK_H
