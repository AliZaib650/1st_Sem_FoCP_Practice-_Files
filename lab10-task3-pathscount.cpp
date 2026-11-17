#include <iostream>
using namespace std;

int countPaths(int m, int n)
{
    if (m == 1 || n == 1)
        return 1;

    return countPaths(m - 1, n) + countPaths(m, n - 1);
}

int main()
{
    int m, n;

    cout << "Enter number of rows: ";
    cin >> m;

    cout << "Enter number of columns: ";
    cin >> n;

    while (m <= 0 || n <= 0)
    {
        cout << "Invalid grid dimensions." << endl;
        cout << "Dimensions must be positive." << endl;

        cout << "Enter number of rows: ";
        cin >> m;

        cout << "Enter number of columns: ";
        cin >> n;
   
    }

    cout << "Number of unique paths: " << countPaths(m, n);

    return 0;
}