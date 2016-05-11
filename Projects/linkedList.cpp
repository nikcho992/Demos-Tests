#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

template <typename T>
struct Box
{
    T data;
    Box<T> *next;

    Box(const T& d,Box<T> *n)
    {
        data=d;
        next=n;
    }
};

template<typename T>
class List
{
private:
    Box<T> *first;
public:
    List()
    {
        first=NULL;
    }

    List(const List<T>& other)
    {
        Box<T> *crr=other.first,*previous;

        if(other.first == NULL)
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
        Box<T> *crr=first,*save;

        while(crr!=NULL)
        {
            save=crr;
            crr=crr->next;

            delete save;
        }
    }

    Box<T>* getFirst()
    {
        return first;
    }

    List<T>& push (const T& other)
    {
        Box<T> *newbox=new Box<T>(other,NULL);
        newbox->next=first;
        first=newbox;

        return *this;
    }

    List<T>& pushBack(const T& other)
    {
        Box<T> *newbox=new Box<T>(other,NULL);
        Box<T> *crr=first;

        while(crr->next!=NULL)
        {
            crr=crr->next;
        }

        crr->next=newbox;
        return *this;
    }

    List<T>& operator += (const T& newElement)
    {
        return pushBack(newElement);
    }

    List<T>& getElement(int n)
    {
        Box<T> *crr=first;
        int temp=0;

        while(n--)
        {

            assert(crr!=NULL);
            crr=crr->next;

        }

        return crr->data;

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


    List<T> append(List<T>& other)
    {
        Box<T> *crr=other.getFirst();
        while(crr!=NULL)
        {
            this->pushBack(crr->data);
            crr=crr->next;
        }
        return *this;
    }


    List<T> concat(List<T>& other)
    {
        List<T> result=*this;
        result.append(other);

        return result;
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
   list1.pushBack(123);
   //cout<<list1<<endl;

    List<int> list2=list1;
    list2[0]=888;
    //cout<<list2<<endl;
    List<int> list3= list1.concat(list2);
    cout<<list1.concat(list2)<<endl;
    //cout<<list3<<endl;




}
