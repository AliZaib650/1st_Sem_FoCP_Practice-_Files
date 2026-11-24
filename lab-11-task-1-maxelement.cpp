#include<iostream>
using namespace std;

int maxElement(const int arr[],int size)
{
    static int max = arr[0];
    if(size==0)
    return max;

    if(arr[size-1]>max)
    {max = arr[size-1];}

    return maxElement(arr, size-1);
}
int main()
{
    int size;
    cout << "Enter Size of Array: " ;
    cin >> size;

    while(size<=0){
        cout << "invalid size of array" << endl;
        cout << "Enter Size of Array: " ;
        cin >> size;
    }

    int arr[size];

    for(int i=0; i<size; i++)
    {
        cout << "Enter element " << i+1 << " : " ;
        cin >> arr[i];
    }

    cout << "Max Element of array is : " << maxElement(arr, size); 
    return 0;
}