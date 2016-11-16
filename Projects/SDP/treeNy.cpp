#include <iostream>
#include <assert.h>
#include <cstring>
#include <algorithm>
#include <iomanip>

using namespace std;

template<class T>
using mapFn = bool (*)(const T&);

template<class T>
using mapFn2 = T (*)(const T&);


template <class T>
struct Node
{
	Node<T>* left;
	Node<T>* right;
	T data;

	Node(const T& d,Node<T>* l,Node<T>* r): data(d),left(l),right(r){}
	Node():left(NULL),right(NULL){}
};

template <class T>
class BTree
{
private:
	Node<T>* root;
	bool add(const T& data,const char* trace, Node<T>*&); /// !!!
	void insertBOT (Node<T>*&subTreeRoot,const T& x);
	void simplePrint(Node<T>* subTreeRoot) const;
	void prettyPrint (Node<T>* subTreeRoot,int space);
	void deleteAll(Node<T>* subTreeRoot);
   	bool member(const T& data,Node<T>* subTreeRoot) const;
	void mapFunc(mapFn2<T> f,Node<T>* subTreeRoot);
   	int countMembers(Node<T>* subTreeRoot);
   	int countEvens(Node<T>* subTreeRoot);
  	int searchMap(Node<T>* subTreeRoot,mapFn<T> f);
  	int height(Node<T>* subTreeRoot);
  	int countLeaves(Node<T>* subTreeRoot);
  	T& maxLeaf(Node<T>* subTreeRoot,T currentMax);
  	void inorderPrint(Node<T>* subTreeRoot);
  	void preorderPrint(Node<T>* subTreeRoot);
  	void postorderPrint(Node<T>* subTreeRoot);
  	int longestConsecutive (Node<T>* subTreeRoot,int currentLen,int expectedNext);
  	bool isFull (Node<T>* subTreeRoot,int height,int layer);



public:
	BTree();
	~BTree();
	BTree<T>& add(const T& data,const char* trace);
	BTree<T>& insertBOT (const T& x);
	void simplePrint() const;
	void prettyPrint();
	void deleteAll();
	bool member(const T& data) const;
	void mapFunc (mapFn2<T> f);
	int countMembers();
	int countEvens();
	int searchMap(mapFn<T> f);
	int height();
	int countLeaves();
	T& maxLeaf();
	void inorderPrint();
	void preorderPrint();
	void postorderPrint();
	int longestConsecutive();
	bool isFull();

};

template<class T>
BTree<T>::BTree(): root(NULL){}

template <class T>
BTree<T>& BTree<T>::add(const T& data,const char* trace)
{
	add(data,trace,root);
	return *this;
}

template <class T>
bool BTree<T>::add(const T& data,const char* trace,Node<T>* &subTreeRoot)
{
	if(subTreeRoot == 0)
	{
		assert(strlen(trace) == 0);
		subTreeRoot = new Node<T>(data,NULL,NULL);
		return true;
	}

	assert(strlen(trace)>0);

	if(trace[0]=='L')
	{
		return add(data,trace+1,subTreeRoot->left);
	}

	assert(trace[0] == 'R');

	return add(data,trace+1,subTreeRoot->right);

	return true;
}

template<class T>
void BTree<T>::simplePrint() const
{
	simplePrint(root);
}

template <class T>
void BTree<T>::simplePrint(Node<T>* subTreeRoot) const
{
	if(subTreeRoot == NULL)
		return;

	cout<<subTreeRoot->data<<" ";
	simplePrint(subTreeRoot->left);
	simplePrint(subTreeRoot->right);
}

template <class T>
void BTree<T>:: prettyPrint()
{
	prettyPrint(root,0);
}

template<class T>
void BTree<T>::prettyPrint(Node<T>* subTreeRoot,int space)
{
	if (subTreeRoot == NULL)
	{
		return;
	}

	if (subTreeRoot->right != NULL)
	{
		prettyPrint(subTreeRoot->right,space+6);
	}

	if (space != 0)
	{
		cout << setw(space) << " ";
	}

	if (subTreeRoot->right != NULL)
	{
		cout << endl << setw(space) << " ";
	}
	cout << subTreeRoot->data;

	if (subTreeRoot->left != NULL)
	{
		cout << setw(space) << " "<<endl;
		prettyPrint(subTreeRoot->left, space + 6);
	}
}

template <class T>
void BTree<T>::deleteAll()
{
	deleteAll(root);
}

template <class T>
void BTree<T>::deleteAll(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return;

	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

template<class T>
BTree<T>::~BTree()
{
	deleteAll(root);
}

template<class T>
bool BTree<T>::member(const T& data) const
{
	return member(data,root);
}

template<class T>
bool BTree<T>::member(const T& data,Node<T>* subTreeRoot) const
{
	if(subTreeRoot == NULL)
		return false;

	return subTreeRoot->data == data ||
		   member(data,subTreeRoot->left) ||
		   member(data,subTreeRoot->right);
}

template<class T>
void BTree<T>::mapFunc(mapFn2<T> f)
{
	mapFunc(f,root);
}

template<class T>
void BTree<T>::mapFunc(mapFn2<T> f,Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return;

	subTreeRoot->data = f(subTreeRoot->data);
	mapFunc(f,subTreeRoot->left);
	mapFunc(f,subTreeRoot->right);
}

int plusOne(const int& i)
{
	return i + 1;
}

int multByTwo(const int& i)
{
	return i*2;
}

template<class T>
int BTree<T>::countMembers()
{
	return countMembers(root);
}

template<class T>
int BTree<T>::countMembers(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	return countMembers(subTreeRoot->left) + countMembers(subTreeRoot->right) + 1;
}

template<class T>
int BTree<T>::countEvens()
{
	return countEvens(root);
}

template<class T>
int BTree<T>::countEvens(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
		return NULL;

	int res = (subTreeRoot->data % 2 == 0) ? 1:0;

	return res + countEvens(subTreeRoot->left) + countEvens(subTreeRoot->right);
}

template<class T>
int BTree<T>::searchMap(mapFn<T> f)
{
	return searchMap(root, f);
}

template<class T>
int BTree<T>::searchMap(Node<T>* subTreeRoot, mapFn<T> f)
{
	if (subTreeRoot == NULL)
		return 0;

	if (f(subTreeRoot->data))
	{
		return searchMap(subTreeRoot->left, f) + searchMap(subTreeRoot->right, f) + 1;
	}
	else
	{
		return searchMap(subTreeRoot->left, f) + searchMap(subTreeRoot->right, f);
	}
}


bool divByThree(const int& x)
{
	return x % 3 == 0;
}

bool isHundred(const int& x)
{
	return x>=100 && x<=999;
}

template<class T>
int BTree<T>::height()
{
	return height(root);
}

template<class T>
int BTree<T>::height(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	if(height(subTreeRoot->left) > height(subTreeRoot->right))
	{
		return height(subTreeRoot->left) + 1;
	}
	else
	{
		return height(subTreeRoot->right) + 1;
	}
}

template<class T>
int BTree<T>::countLeaves()
{
	return countLeaves(root);
}

template<class T>
int BTree<T>::countLeaves(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL )
	{
		return 1;
	}

	else
	{
		return countLeaves(subTreeRoot->left) + countLeaves(subTreeRoot->right);
	}
}

template<class T>
T& BTree<T>::maxLeaf()
{
	return maxLeaf(root,0);

}

template<class T>
T& BTree<T>::maxLeaf(Node<T>* subTreeRoot,T currentMax)
{
	if(subTreeRoot == NULL)
		return currentMax;

	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL )
	{
		currentMax = currentMax > subTreeRoot->data ? currentMax : subTreeRoot->data;
	}


	T leftMax = maxLeaf(subTreeRoot->left,currentMax);
	T rightMax = maxLeaf(subTreeRoot->right,currentMax);

	return leftMax > rightMax ? leftMax : rightMax;
}

template<class T>
void BTree<T>::insertBOT (Node<T>* &subTreeRoot,const T& x)
{

	if (subTreeRoot == NULL)
	{
		subTreeRoot = new Node<T> (x,NULL,NULL);
		return;
	}

	if (x <= subTreeRoot->data)
	{
		insertBOT (subTreeRoot->left,x);
	} else {
		insertBOT (subTreeRoot->right,x);
	}

}


template<class T>
BTree<T>& BTree<T>::insertBOT (const T& x)
{
	insertBOT (root,x);
	return *this;
}



template<class T>
void BTree<T>:: inorderPrint()
{
    inorderPrint(root);
}

template<class T>
void BTree<T>:: inorderPrint(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
        return ;

    if(subTreeRoot->left)
        {
            inorderPrint(subTreeRoot->left);
        }

    cout<<subTreeRoot->data<<" ";

    if(subTreeRoot->right)
        {
            inorderPrint(subTreeRoot->right);
        }
}

template<class T>
void BTree<T>:: preorderPrint()
{
    preorderPrint(root);
}

template<class T>
void BTree<T>:: preorderPrint(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
        return ;

    if(subTreeRoot->left)
        {
            preorderPrint(subTreeRoot->left);
        }

    if(subTreeRoot->right)
        {
            preorderPrint(subTreeRoot->right);
        }
        cout<<subTreeRoot->data<<" ";
}

template<class T>
void BTree<T>:: postorderPrint()
{
    postorderPrint(root);
}

template<class T>
void BTree<T>:: postorderPrint(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
        return ;

     cout<<subTreeRoot->data<<" ";

    if(subTreeRoot->left)
        {
            postorderPrint(subTreeRoot->left);
        }


    if(subTreeRoot->right)
        {
            postorderPrint(subTreeRoot->right);
        }
}

template<class T>
int BTree<T>::longestConsecutive()
{
    return longestConsecutive(root,0,root->data + 1);
}

template<class T>
int BTree<T>::longestConsecutive(Node<T>* subTreeRoot,int currentLen,int expected)
{
    if(subTreeRoot == NULL)
        return currentLen;

    if(subTreeRoot->data == expected)
        {
            currentLen += 1;
        }
    else
        {
            currentLen = 0;
        }

    int left = longestConsecutive(subTreeRoot->left,currentLen,expected + 1);
    int right = longestConsecutive(subTreeRoot->right,currentLen,expected + 1);

    return max(currentLen, max(left,right));

}

template<class T>
bool BTree<T>::isFull()
{
    int h = height() - 1;
    return isFull(root,h,0);
}

template<class T>
bool BTree<T>::isFull(Node<T>* subTreeRoot,int height,int layer)
{
    if(layer == height)
        return 1;

    if((subTreeRoot->left == NULL || subTreeRoot->right == NULL) && layer < height)
        return 0;

    return isFull(subTreeRoot->left,height,layer + 1) && isFull(subTreeRoot->right,height,layer + 1);

}

int main()
{
	BTree<int> tree;
	BTree<int> tree2;

	//tree2.add(9,"").add(10,"L").add(12,"R").add(11,"LL");//.add(1,"LR");
	//tree2.prettyPrint();

	tree.insertBOT(1)
	 .insertBOT(3)
	 .insertBOT(4)
	 .insertBOT(6)
	 .insertBOT(5)
	 .insertBOT(66);
	// .insertBOT(60)
	 //.insertBOT(65)
	 //.insertBOT(59);

    //cout<<endl;
    tree.prettyPrint();
    cout<<endl;
    cout<<tree.longestConsecutive();
    //cout<<tree.isFull();

   /* tree.inorderPrint();
    cout<<endl;
    tree.preorderPrint();
    cout<<endl;
    tree.postorderPrint();
    cout<<endl;*/

   // cout<<tree.searchMap(isHundred)<<endl;


	//if(tree.countLeaves() == 3)
		//cout<<"Passed countLeaves() "<<endl;

	//if(tree.countMembers() == 4)
		//cout<<"Passed countMembers()"<<endl;

    //if(tree.maxLeaf() == 15)
      //  cout<<"Passed maxLeaf() "<<endl;

	//tree.map(plusOne);
	//tree.simplePrint();

	//tree.mapFunc(multByTwo);

 	/*cout<<endl;
  	if(tree.countEvens() == 2)
    {
        cout<<"Passed";
    }*/

    /*if(tree.searchMap(isHundred) == 2)
    	cout<<"Passed 1"<<endl;
    if(tree.searchMap(divByThree) == 1)
    	cout<<"Passed 2"<<endl;*/


	/*if(tree.member(10))
	{
		cout<<"Member1 found."<<endl;
	}
	else
	{
		cout<<"Member1 not found."<<endl;
	}
	if(tree.member(1111))
	{
		cout<<"Member2 found."<<endl;
	}
	else
	{
		cout<<"Member2 not found."<<endl;
	}*/

	return 0;
}
