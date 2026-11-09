#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void Create(int** a, int n, int m, int low, int high, int i = 0, int j = 0) // випадкові числа
{
    if (i == n)
        return;

    a[i][j] = low + rand() % (high - low + 1);

    if (j + 1 < m) // спочатку ідемо по рядкам в стовпці , а потім переходим до наступного рядка
        Create(a, n, m, low, high, i, j + 1); 
    else
        Create(a, n, m, low, high, i + 1, 0);
}

void Print(int** a, int n, int m, int i = 0, int j = 0) // виведення
{
    if (i == n)
        return;

    cout << setw(5) << a[i][j];

    if (j + 1 < m)
        Print(a, n, m, i, j + 1);
    else
    {
        cout << endl;
        Print(a, n, m, i + 1, 0);
    }
}

int MaxColumn(int** a, int n, int j, int i, int max) // знаходження максимума в конкретному стовпці
{
    if (i == n)
        return max;

    if (a[i][j] > max)
        max = a[i][j];

    return MaxColumn(a, n, j, i + 1, max);
}

int SearchMinMax(int** a, int n, int m, int j, int min) // знаходженння найменшого серед максимумів непарних стовпців
{
    if (j >= m)
        return min;

    int max = MaxColumn(a, n, j, 1, a[0][j]); 

    if (max < min)
        min = max;

    return SearchMinMax(a, n, m, j + 2, min); // запускаємо пошук в непарних стовпцях максимальних значень
}

int main()
{
    srand((unsigned)time(NULL));

    int n = 5, m = 6;
    int low = -10, high = 20;

    int** a = new int* [n];

    for (int i = 0; i < n; i++)
        a[i] = new int[m];

    Create(a, n, m, low, high);

    cout << "Matrix:" << endl;
    Print(a, n, m);

    int min = MaxColumn(a, n, 1, 1, a[0][1]);

    int result = SearchMinMax(a, n, m, 3, min);

    cout << "Result = " << result << endl;

    for (int i = 0; i < n; i++)
        delete[] a[i];

    delete[] a;

    return 0;
}
