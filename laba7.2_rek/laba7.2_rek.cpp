#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void Create(int** a, int rowCount, int colCount, int Low, int High, int i = 0, int j = 0)
{
    if (i == rowCount)
        return;

    a[i][j] = Low + rand() % (High - Low + 1);

    if (j + 1 < colCount)
        Create(a, rowCount, colCount, Low, High, i, j + 1);
    else
        Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** a, int rowCount, int colCount, int i = 0, int j = 0)
{
    if (i == rowCount)
    {
        cout << endl;
        return;
    }

    cout << setw(5) << a[i][j];

    if (j + 1 < colCount)
        Print(a, rowCount, colCount, i, j + 1);
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0);
    }
}

int MaxColumn(int** a, int rowCount, int j, int i, int max)
{
    if (i == rowCount)
        return max;

    if (a[i][j] > max)
        max = a[i][j];

    return MaxColumn(a, rowCount, j, i + 1, max);
}

int SearchMinMax(int** a, int rowCount, int colCount, int j, int min)
{
    if (j >= colCount)
        return min;

    int max = MaxColumn(a, rowCount, j, 1, a[0][j]);

    if (max < min)
        min = max;

    return SearchMinMax(a, rowCount, colCount, j + 2, min);
}

int main()
{
    srand((unsigned)time(NULL));

    int rowCount = 5;
    int colCount = 6;
    int Low = -10;
    int High = 20;

    int** a = new int* [rowCount];

    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);

    cout << "Matrix:";
    Print(a, rowCount, colCount);

    int min = MaxColumn(a, rowCount, 1, 1, a[0][1]);

    int result = SearchMinMax(a, rowCount, colCount, 3, min);

    cout << "Result = " << result << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];

    delete[] a;

    return 0;
}
