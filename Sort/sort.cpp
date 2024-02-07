/*

сортировка слиянием имеет доказанную трудоёмкость в худшем случае
O(n*logn)

*/

#include <iostream>
using namespace std;

//put array, first and last index
void mergeSortImpl(int *arr, int left, int right, int *tmp)
{
    if (left == right) return;
    
    int mid = (right - left - 1) / 2 + left;
    mergeSortImpl(arr, left, mid, tmp);
    mergeSortImpl(arr, mid + 1, right, tmp);

    int i = left, j = mid + 1, k = 0;
    while(i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
    }
    int x = k;
    while (i <= mid)
    {
        arr[left + x++] = arr[i++];
    }
    for (x = 0; x < k; x++)
    {
        arr[left + x] = tmp[x];
    }
}

void mergeSort(int *arr, int len)
{
    int *tmp = new int[len];
    mergeSortImpl(arr, 0, len - 1, tmp);
    delete[] tmp;
}

bool test(int *a, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        if(a[i] > a[i+1]) return false;
    }
    return true;
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout<<a[i]<<"  ";
    }
    cout<<endl;
}

int main()
{
    int n = 6000;
    int a[n];
    bool ok = true;

    for (int j = 0; j < 1000; j++)
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() - RAND_MAX/2;
        }
        mergeSort(a,n);
        if (!test(a,n)) ok = false;
    }

    if (ok) cout<<"ok\n";

    return 0;
}
