#define INITSIZE 16
#define INVALID -1
// DEQUE Implementation.
using namespace std;
namespace gaurav{
template <class T>
class deque{
    int qsize;
    T *ptr;
    int fronti;
    int reari;
public:
// ● deque() - initialize a blank deque.
deque(int n)
{
    n++;
    ptr = new T[n];
    qsize = n;
    fronti = 0;
    reari = 0;
    for(int i=0;i<n;i++)
        ptr[i] = INVALID;
}
// ● deque(n,x) - initialize a deque of length n with all values as x.
deque(unsigned int length, T value)
{
    length++;
    ptr = new T[length];
    qsize = length;
    for(int i=0;i<qsize;i++)
    {
        push_back(value);
    }
    fronti = 0;
    reari = qsize-1;
}
// ● push_back(x) - append data x at the end.
void push_back(T value)
{
    if((reari + 1 + qsize)%qsize == fronti)
    {
        int old_size = qsize;
        qsize = qsize<<1;
        T *newptr;
        newptr = new T[qsize];
        int j=0;
        for(int i=fronti;i!=reari;i = (i+1+old_size)%old_size)
        {
            newptr[j++] = ptr[i];
        }
        reari=(j+qsize)%qsize;
        fronti=0;
        free(ptr);
        ptr = newptr;
    }
    ptr[(reari)%qsize] = value;
    reari = (reari + 1 + qsize)%qsize;
}
// ● pop_back() - erase data at the end.
void pop_back()
{
    if(fronti == reari)
    {
        cout<<"Deque empty. Pop failed"<<endl;
        return;
    }
    ptr[reari]=INVALID;
    reari = (reari-1+qsize)%qsize;
}
// ● push_front(x) - append data x at the beginning.
void push_front(T value)
{
    if((fronti-1+qsize)%qsize == reari)
    {
        int old_size = qsize;
        qsize = qsize<<1;
        T *newptr;
        newptr = new T[qsize];
        int j=1;
        for(int i=fronti;i!=reari;i = (i+1+old_size)%old_size)
        {
            newptr[j++] = ptr[i];
        }
        reari=(j+qsize)%qsize;
        fronti=1;
        free(ptr);
        ptr = newptr;
    }
    ptr[(fronti-1 + qsize)%qsize]=value;
    fronti = (fronti - 1 + qsize)%qsize;
}
// ● pop_front() - erase data at the beginning.
void pop_front()
{
    ptr[fronti]=INVALID;
    if(fronti == reari)
    {
        cout<<"Deque empty. Pop failed"<<endl;
        return;
    }
    fronti = (fronti+1+qsize)%qsize;
}
// ● front() - returns the first element(value) in the deque.
T front()
{
    return ptr[fronti];
}
// ● back() - returns the last element(value) in the deque.
T back()
{
    return ptr[(reari-1+qsize)%qsize];
}
// ● empty() - returns true if deque is empty else returns false.
bool empty()
{
    if(fronti == reari)
        return true;
    return false;
}
// ● size() - returns the current size of deque.
int size()
{
    return (qsize-1);
}
// ● resize(x) - changes the size dynamically.
void resize(int siz)
{
    siz++;
    int temp = siz;
    if(siz < qsize)
    {
        T *newptr = new T[siz];
        int j=0;
        for(int i=fronti;((i!=reari) && (siz--));i=(i+1+qsize)%qsize)
        {
            newptr[j++] = ptr[i];
        }
        fronti=0;
        reari=j-1;
        qsize=temp;
        free(ptr);
        ptr=newptr;
        return;
    }
    if(siz == qsize)
    {
        return;
    }
    if(siz > qsize)
    {
        T *newptr = new T[siz];
        int j=0;
        for(int i=fronti;(i!=reari);i=(i+1+qsize)%qsize)
        {
            newptr[j++] = ptr[i];
        }
        fronti=0;
        reari=j;
        qsize = temp;
        free(ptr);
        ptr=newptr;
        return;
    }
}
// ● clear() - remove all elements of deque.
void clear()
{
    T *newptr = new T[INITSIZE];
    qsize = INITSIZE;
    for(int i=0;i<INITSIZE;i++)
        newptr[i]=INVALID;
    free(ptr);
    ptr = newptr;
    fronti = 0;
    reari = 0;
}
// ● D[n] - returns the nth element of the deque.
T operator [] (int n)
{
    if(ptr[(fronti + n - 1)%qsize]!=INVALID)
        return ptr[(fronti + n - 1)%qsize];
    else
        return INVALID;
}
void printdq()
{
    for(int i=fronti;i!=reari%qsize;i=(i+1)%qsize)
    {
        cout<<ptr[i]<<" ";
    }
    cout<<endl;
}

void p()
{
    cout<<"front "<<fronti<<"rear "<<reari<<endl;
}

void removekey(T key)
{
    int index = find(key);
    if(index == INVALID)
    {
        //cout<<"Not found in deque"<<endl;
        return;
    }else{
        for(int i=index;(i+1)!=reari;i=(i+1+qsize)%qsize)
        {
            ptr[i] = ptr[i+1];
        }
        reari = (reari - 1)%qsize;
    }
}

int find(T key)
{
    for(int i=fronti;i!=reari;i=(i+1+qsize)%qsize)
    {
        if(ptr[i] == key)
            return i;
    }
    return INVALID;
}

T* getArray()
{
    T* arr = new T[validSize()+1];
    int l=0;
    for(int i=fronti;i!=reari;i=(i+1+qsize)%qsize)
    {
        arr[l]=ptr[i];
        l++;
    }
    arr[l]='\0';
    return arr;
}

int validSize()
{
    return (reari-fronti+qsize)%qsize;
}
};
}
