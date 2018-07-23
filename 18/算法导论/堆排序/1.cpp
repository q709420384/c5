/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年05月19日 星期六 19时13分03秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

int parent(int i)
{
    return (i-1)/2;
}
int left(int i)
{
    return 2*i + 1;
}
int right(int i)
{
    return 2*(i + 1);
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void maxHeapify(vector<int> &arr, int i, int n)
{
    int large;
    int l = left(i);
    int r = right(i);
    int size = arr.size();
    if(l < size && l < n && arr[i] < arr[l])
        large = l;
    else large = i;
    if(r < size && r < n && arr[large] < arr[r])
        large = r;
    if(large != i)
    {
        swap(arr[i], arr[large]);
        maxHeapify(arr, large, n);
    }
}
void buildMaxHeap(vector<int> &arr)
{
    int n = arr.size();
    for(int i = arr.size()/2 - 1; i >= 0; --i)
    {
        maxHeapify(arr, i, n);
    }
}
void heapSort(vector<int> &arr)
{
    buildMaxHeap(arr);
    int n = arr.size() - 1;
    for(int i = n; i > 0; --i)
    {
        swap(arr[0], arr[n]);
        n -= 1;
        maxHeapify(arr, 0, n);
    }
}
int main()
{
    int a[10] = {123,2,34,544,878,7,9879,6,546,1223};
    vector<int> arr(a, a + 10);
    vector<int>::iterator it;
    heapSort(arr);
    for(it=arr.begin(); it != arr.end();++it)
    {
        cout << *it << endl;
    }
}
