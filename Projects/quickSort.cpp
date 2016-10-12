#include <iostream>

using namespace std;


void quickSort(int arr[],int left,int right)
{
    int i = left;
    int j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];


    //PARTITION

    while( i <= j)
        {
            while(arr[i] < pivot)
                i++;

            while(arr[j] > pivot)
                j--;

            if(i <= j)
                {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;

                    i++;
                    j--;
                }
        };


        if(left < j)
            {
                quickSort(arr,left,j);
            }
        if(i < right)
            {
                quickSort(arr,i,right);
            }
}

int main()
{
    int arr[5] = {12,3,6,111,-31};
    quickSort(arr,0,5);

    for(int i=0;i<5;i++){
            cout<<arr[i]<<" ";
    }
}
