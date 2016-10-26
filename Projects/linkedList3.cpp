#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

template <typename T>
struct Box
{
    T data;
    Box<T>* next;

    Box(const T& d,Box<T> *n):data(d),next(n){};
};

template<typename T>
class List
{
private:
    Box<T>* first;
public:

    List()
    {
        first=NULL;
    }

    List(const List<T>& other)
    {
        Box<T>* crr=other.first,*previous;

        if(other.first==NULL)
        {
            first=NULL;
            return;
        }

        first= new Box<T>(crr->data,NULL);
        previous=first;
        crr=crr->next;

        while(crr!=NULL)
        {
            previous->next=new Box<T>(crr->data,NULL);
            previous=previous->next;

            crr=crr->next;
        }
    }

    ~List()
    {
        Box<T>* crr=first,*save;

        while(crr!=NULL)
        {
            save=crr;
            crr=crr->next;

            delete save;
        }
    }

    List<T>& push (const T& other)
    {
        Box<T> *newbox=new Box<T>(other,NULL);
        newbox->next=first;
        first=newbox;

        return *this;
    }

    T get(int index)
    {
        Box<T>* crr=first;

        while(index--)
        {
            assert(crr!=NULL);
            crr=crr->next;
        }
        return crr->data;
    }

    int getElem(T elem)
    {
        Box<T>* crr=first;
        int index=0;

        while(crr->data != elem)
        {
            crr=crr->next;
            index++;
        }
        return index;
    }

     T operator [] (int i) const
	{
		assert (i >= 0);

		Box<T> *crr = first;

		while (crr != NULL && i > 0)
		{
			crr = crr->next;
			i--;
		}

		assert (crr != NULL);
		return crr->data;

	}

	 T& operator [] (int i)
	{

		assert (i >= 0);

		Box<T> *crr = first;

		while (crr != NULL && i > 0)
		{
			crr = crr->next;
			i--;
		}

		assert (crr != NULL);
		return crr->data;

	}

    void addElement(T elem,int index)
    {
        Box<T>* crr=first;
        Box<T>* newbox = new Box<T>(elem,NULL);

        int counter=0;

        while(crr->next!=NULL)
        {
            if(counter == index-1)
            {
                newbox->next=crr->next;
                crr->next=newbox;
            }
            crr=crr->next;
            counter++;

        }
       //return *this;

    }

    List<T> removeElem(T elem)
    {
        Box<T>* crr=first,*save;

        while(crr->next != NULL)
        {
            if(crr->data == elem)
            {
                save=crr->next;
                crr->next=crr->next->next;
                delete save;
                break;
            }
            crr=crr->next;

        }

        return *this;
    }
	
	 void pop()
    {
         Box<T>* save;

         save = first;
         first = first->next;

        delete save;

    }

    template<class U>
    friend ostream& operator <<(ostream& out,const List<U>& list);



};
template<class U>
ostream& operator << (ostream& out,const List<U>& list1)
{
    Box<U> *crr=list1.first;

    while(crr!=NULL)
    {
        out<<crr->data<<" ";
        crr=crr->next;
    }

    return out;
}

int main()
{
    List<int> list1;
    //List<int> list2;
    //List<int> list3(list1);
    list1.push(1);
    list1.push(2);
    list1.push(3);
    list1.pop();

   // cout<<list1.get(1);
    //cout<<list1.getElem(3);

    list1.addElement(888,2);
    list1[1] = 7;
    //cout<<list1[0]<<endl;
    cout<<list1;


}
