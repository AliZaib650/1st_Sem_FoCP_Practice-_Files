#include<iostream>
using namespace std;

bool isSorted(const int arr[],int n)
{
    if(n<=1)
    return true;

    if(arr[n-1]<arr[n-2])
    {return false;}
    
    return isSorted(arr, n-1);
}

int main()
{
    int n;
    cout << "Enter Size of Array: " ;
    cin >> n;

    while(n<=0){
        cout << "invalid size of array" << endl;
        cout << "Enter Size of Array: " ;
        cin >> n;
    }

    int arr[n];

    for(int i=0; i<n; i++)
    {
        cout << "Enter element " << i+1 << " : " ;
        cin >> arr[i];
    }

    if(isSorted(arr, n))
    {cout << "The Array is sorted.";}
    else
    {cout << "The array is not sorted";}
    return 0;
}