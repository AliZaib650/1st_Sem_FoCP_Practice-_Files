#include <iostream>
using namespace std;

int sumArray(int arr[], int size, int index)
{
    if (index == size)
        return 0;

    return arr[index] + sumArray(arr, size, index + 1);
}

int countOccurrences(int arr[], int size, int index, int target)
{
    if (index == size)
        return 0;

    if (arr[index] == target)
        return 1 + countOccurrences(arr, size, index + 1, target);

    return countOccurrences(arr, size, index + 1, target);
}

int main()
{
    int size = 7, target;
    int arr[7] = {2, 3, 2, 6, 3, 2, 4};
    target = 2;
    cout << "Sum of array elements is: " << sumArray(arr, size, 0) << endl;

    cout << "Occurrences of " << target << " is : " << countOccurrences(arr, size, 0, target);

    return 0;
}
