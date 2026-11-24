#include<iostream>
using namespace std;

int ReversePrint(int arr[], int size)
{
    if (size==0)
    return arr[0];

    cout << arr[size-1] << " ";
    return ReversePrint(arr, size-1);
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

    cout << "Array in reverse order: ";
    ReversePrint(arr, size);

    return 0;
}