#include <iostream>

template <typename TYPE>
class ListRingBuffer
{
    struct List
    {
        TYPE elem;
        List *next;
    };
    List *start = NULL;
    List *end = NULL;

public:
    ~ListRingBuffer()
    {
        if (!start) return;
        List *var = start;
        do
        {
            end = var->next;
            delete var;
            var = end;
        } while(var != start);
    }
    void push(TYPE val)
    {
        if (!start)
        {
            start = new List;
            start->next = start;
        }
        else if (start->next == end)
        {
            List *var = new List;
            var->next = start->next;
            start->next = var;
            start = var;
        }
        else
        {
            start = start->next;
        }
        start->elem = val;
        if (!end) end = start;  //if buffer was empty
    }
    TYPE pop()
    {
        if (!end) throw std::out_of_range("the buffer is empty");
        TYPE res = end->elem;
        if (end == start) end = NULL;   //we extract the last element
        else end = end->next;
        return res;
    }
    void print_all()
    {
        if (!start) return;
        std::cout<<"all: ";
        List *var = start;
        do
        {
            std::cout<<var->elem<<"  ";
            var = var->next;
        } while (var != start);
        std::cout<<std::endl;
    }
    void print_queue()
    {
        if (!end) return;
        std::cout<<"line: ";
        List *var = end;
        do
        {
            std::cout<<var->elem<<"  ";
            var = var->next;
        } while (var != start);
        std::cout<<var->elem<<std::endl;
    }
};

int main()
{
    ListRingBuffer<int> b;
    b.push(1);
    b.print_all();
    b.push(2);
    b.print_all();
    b.push(3);
    b.print_all();
    std::cout<<"pop: "<<b.pop()<<"\n";
    b.push(4);
    b.print_all();
    b.push(5);
    b.print_all();
    std::cout<<"pop: "<<b.pop()<<"\n";
    std::cout<<"pop: "<<b.pop()<<"\n";
    b.print_all();
    b.print_queue();

    std::cout<<std::endl;
    return 0;
}