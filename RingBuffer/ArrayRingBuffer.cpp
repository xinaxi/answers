#include <iostream>
using namespace std;

template <typename TYPE>
class ArrayRingBuffer
{
    TYPE* arr = NULL;
    int n = 0;
    int start = 0;
    int end = 0;
    bool empty = true;
    int next(int i)
    {
        return (i < n-1) ? i + 1 : 0;
    }

public:
    ArrayRingBuffer(int n) : n(n)
    {
        arr = new TYPE[n];
    }
    ~ArrayRingBuffer()
    {
        delete[] arr;
    }
    void push(TYPE elem)
    {
        arr[start] = elem;
        if (start == end && !empty)
        {
            end = next(end);    //forget oldest element
        }
        start = next(start);
        empty = false;
    }
    TYPE pop()
    {
        if (empty) throw out_of_range("the buffer is empty");
        TYPE res = arr[end];
        end = next(end);
        if (end == start) empty = true;
        return res;
    }
    void print_all()
    {
        cout<<"all: ";
        for (int i = 0; i < n; i++)
        {
            cout<<arr[i]<<"  ";
        }
        cout<<endl;
    }
    void print_queue()
    {
        if (empty) return;
        cout<<"line: ";
        int i = end;
        do
        {
            cout<<arr[i]<<"  ";
            i = next(i);
        } while (i != start);
        cout<<endl;
    }
};

int main()
{
    ArrayRingBuffer<int> b(5);
    b.push(1);
    b.push(2);
    b.push(3);
    b.print_all();
    b.print_queue();
    cout<<"pop: "<<b.pop()<<endl;
    b.print_queue();
    b.push(4);
    b.push(5);
    b.push(6);
    b.push(7);
    b.print_all();
    b.print_queue();
    cout<<"pop: "<<b.pop()<<endl;
    
    cout<<endl;
    return 0;
}