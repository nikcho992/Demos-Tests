#include <iostream>

using namespace std;

int binarySearch(int arr[],int value,int left,int right){

if(left > right)
    return -1;

int middle = (left + right)/2;

if(arr[middle] == value)
    return middle;

else if(arr[middle] > value)
    return binarySearch(arr,value,left,middle-1);

else return binarySearch(arr,value,middle+1,right);

}

int main()
{
    int arr[6] = {1,2,3,4,5,6};
    cout<<"The index of the searched value is: "<<binarySearch(arr,2,0,5);
}
