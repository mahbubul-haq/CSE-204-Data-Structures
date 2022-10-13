#include <iostream>
#include<cstdio>
#include <vector>
#include <iterator>
using namespace std;

class Heap {
public:
    Heap();
    ~Heap();
    void insert(int element);
    int extract_max();
    void print();
    int size() { return heap.size(); }
    int find_max();
    void delete_max();
    bool is_empty(){
        if(heap.size()<=0){
            return true;
        }
        return false;
    }

    int getValat(int index){
        return heap.at(index);
    }

    void replace(int value){

        heap[0]=value;
        heapifydown(0);

    }

    void increase_key(int index,int value){
        heap.at(index)=getValat(index)+value;
    }

    void decrease_key(int index,int value){
        heap.at(index)=getValat(index)-value;
    }

    void deleteAN(int index){
        heap.at(index)=(heap.at(heap.size()-1));
        heap.pop_back();
        heapifydown(index);
    }

    Heap * merg(Heap * heap1, Heap * heap2){

        Heap *newHeap=new Heap();

        for(int i=0;i<heap1->size();i++){
            newHeap->insert(heap1->getValat(i));
        }

        for(int i=0;i<heap2->size();i++){
            newHeap->insert(heap2->getValat(i));
        }

        return newHeap;

    }

    Heap * meld(Heap * heap1, Heap * heap2){

        Heap *newHeap=new Heap();

        while(heap1->size()!=0){
            newHeap->insert(heap1->extract_max());
        }

        delete heap1;

        while(heap2->size()!=0){
            newHeap->insert(heap2->extract_max());
        }
        delete heap2;
        return newHeap;

    }

private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
private:
    vector<int> heap;
};

Heap::Heap()
{
}

Heap::~Heap()
{
}

int Heap::find_max(){
    return heap.front();
}

void Heap::insert(int element)
{
    heap.push_back(element);
    heapifyup(heap.size() - 1);
}

int Heap::extract_max()
{
    int max = heap.front();
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0);
    return max;
}

void Heap::delete_max()
{
    heap[0]=heap.at(heap.size()-1);
    heap.pop_back();
    heapifydown(0);
}

void Heap::print()
{
    vector<int>::iterator pos = heap.begin();
    cout << "Heap = ";
    while ( pos != heap.end() ) {
        cout << *pos << " ";
        ++pos;
    }
    cout << endl;
}

void Heap::heapifyup(int index)
{
    //cout << "index=" << index << endl;
    //cout << "parent(index)=" << parent(index) << endl;
    //cout << "heap[parent(index)]=" << heap[parent(index)] << endl;
    //cout << "heap[index]=" << heap[index] << endl;
    while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
            ( heap[parent(index)] <= heap[index] ) )
    {
        int tmp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = tmp;
        index = parent(index);
    }
}

void Heap::heapifydown(int index)
{
    //cout << "index=" << index << endl;
    //cout << "left(index)=" << left(index) << endl;
    //cout << "right(index)=" << right(index) << endl;
    int child = left(index);
    if ( ( child > 0 ) && ( right(index) > 0 ) &&
         ( heap[child] <= heap[right(index)] ) )
    {
        child = right(index);
    }
    if ( child > 0 )
    {
        int tmp = heap[index];
        heap[index] = heap[child];
        heap[child] = tmp;
        heapifydown(child);
    }
}

int Heap::left(int parent)
{
    int i = ( parent << 1 ) + 1; // 2 * parent + 1
    return ( i < heap.size() ) ? i : -1;
}

int Heap::right(int parent)
{
    int i = ( parent << 1 ) + 2; // 2 * parent + 2
    return ( i < heap.size() ) ? i : -1;
}

int Heap::parent(int child)
{
    if (child != 0)
    {
        int i = (child - 1) >> 1;
        return i;
    }
    return -1;
}

int main()
{
    // Creates an empty heap
    Heap* myheap = new Heap();

    int arra[10];
    //700 500 200 800 100 400 900 1000 300 600

    for(int i=0;i<10;i++){
        scanf("%d",&arra[i]);
        myheap->insert(arra[i]);
    }

    myheap->print();
    cout<<endl;

    int heapSize = myheap->size();

    cout<<myheap->find_max()<<endl;
    cout<<myheap->extract_max()<<endl;
    myheap->print();
    myheap->delete_max();
    myheap->print();
    myheap->replace(100);
    myheap->print();

    Heap *heap1=new Heap();
    Heap * heap2=new Heap();

    for(int i=0;i<10;i++){
        scanf("%d",&arra[i]);
        heap1->insert(arra[i]);
        heap2->insert(arra[i]*2);
    }

    Heap * newHeap=myheap->merg(heap1,heap2);
    newHeap->print();
    heap1->print();
    heap2->print();
    Heap * newHeap1=myheap->meld(heap1,heap2);
    newHeap1->print();

    cout<<newHeap1->size()<<endl;
    cout<<newHeap->is_empty()<<endl;
    cout<<newHeap1->find_max()<<endl;

    myheap->increase_key(2,5);
    myheap->print();
    myheap->deleteAN(2);
    myheap->print();



    delete myheap;
}
