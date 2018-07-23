/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月06日 星期二 20时49分28秒
 ************************************************************************/

#include<iostream>
#include<array>
using namespace std;

void show(array<int, 10> arr)
{
    for(int i : arr)
        cout << arr[i];
    cout << endl;
}
int main()
{
    array<int, 10> arr = {2, 3, 1, 0, 4, 7, 5, 8, 9, 6};
    for(int j = 1; j < arr.size(); j++)
    {
        int key = arr[j];
        int i = j - 1;
        while(i >= 0 && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i--;
            show(arr);
        }
        arr[i + 1] = key;
        show(arr);
        puts("");
    }
    show(arr);
}
