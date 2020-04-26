// C program for implementation of binary insertion sort 
#include <stdio.h> 
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;


#pragma region insertion Sort
// A binary search based function to find the position 
// where item should be inserted in a[low..high] 
int binarySearch(vector<int> a, int item, int low, int high)
{
    if (high <= low)
        return (item > a[low]) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item, mid + 1, high);
    return binarySearch(a, item, low, mid - 1);
}

// Function to sort an array a[] of size 'n' 
void insertionSort(vector<int> &a)
{
    int t = 0;
    int i, loc, j, k, selected;

    for (i = 1; i < a.size(); ++i)
    {
        j = i - 1;
        selected = a[i];

        // find location where selected sould be inseretd 
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space 
        while (j >= loc)
        {
            t++;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
    cout << t;
}

void insertionSort(vector<int>& a, int& comp)
{
    comp = 0;
    int i, loc, j, k, selected;

    for (i = 1; i < a.size(); ++i)
    {
        j = i - 1;
        selected = a[i];

        // find location where selected sould be inseretd 
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space 
        while (j >= loc)
        {
            comp++;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }

}
#pragma endregion

#pragma region HeapSort
void PSORT(vector<int>& array, int root, int key, int n, int &comp) {
    int v = root;
    while (2 * v <= n) {
        int LC = 2 * v;
        if (LC<n && array[LC + 1] > array[LC]) {
            LC = LC + 1;
            comp++;
        }
        if (array[LC] > key) {
            array[v] = array[LC];
            v = LC;
            comp++;
        }
        else {
            break;
        }
    }
    array[v] = key;
}

void PSortStart(vector<int> &array, int &comp) 
{
    comp = 0;
    int i, n = array.size();
    array.insert(array.begin(), 0);
    i = n / 2;
    while (i >= 1) {
        PSORT(array, i, array[i], n, comp);
        i--;
    }
    comp = 0;
    i = n;
    while (i >= 2) {
        int max = array[1];
        PSORT(array, 1, array[i], i - 1, comp);
        array[i--] = max;
    }
    array.erase(array.begin());
}
#pragma endregion

#pragma region Merge sort
void MergeList(vector<int>& arr, int s1, int e1, int s2, int e2, int &comp) {
    int fs = s1, fe = e2, i = 0;
    vector<int> temp;
    while (s1 <= e1 && s2 <= e2) {
        if (arr[s1] < arr[s2]) {
            temp.push_back(arr[s1++]);
        }
        else {
            temp.push_back(arr[s2++]);
        }
        comp++;
        ++i;
    }
    if (s1 <= e1) {
        temp.insert(temp.begin() + i, arr.begin() + s1, arr.begin() + e1 + 1);
    }
    else {
        temp.insert(temp.begin() + i, arr.begin() + s2, arr.begin() + e2 + 1);
    }
    swap_ranges(arr.begin() + fs, arr.begin() + fe + 1, temp.begin());
}

void MergeSort(vector<int>& arr, int s, int e, int &comp) 
{
    if (s < e) {
        int md = (s + e) / 2;
        MergeSort(arr, s, md, comp);
        MergeSort(arr, md + 1, e, comp);
        MergeList(arr, s, md, md + 1, e, comp);
    }
}
#pragma endregion

#pragma region Radix Sort
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(vector<int> &arr, int n, int exp)
{
    int *output = new int[n]; // output array 
    int i, count[10] = { 0 };

    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array 
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixsort(vector<int> &arr, int &comp)
{
    // Find the maximum number to know number of digits 
    int m = *max_element(arr.begin(), arr.end());
    comp = arr.size() - 1;

    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, arr.size(), exp);
}

void radixsort(vector<int>& arr)
{
    // Find the maximum number to know number of digits 
    int m = *max_element(arr.begin(), arr.end());

    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, arr.size(), exp);
}
#pragma endregion

#pragma region testcases
void testcaseOutput(vector<int> prev, vector<int> curr, int comparison)
{
    cout << comparison << " - ";
    for (int q = 0; q < prev.size(); ++q)
        cout << prev[q] << " ";
    cout << " => ";
    for (int q = 0; q < prev.size(); ++q)
        cout << curr[q] << " ";
    cout << endl;
}

void testcaseInsertionSort()
{
    vector <int> saved;
    vector <int> a;
    set<int> s;
    int n = 5, i, t, comparison;

    for (int j = 0; j < 100; ++j)
    {
        a.clear();
        s.clear();
        for (i = 0; i < n; ++i)
        {
            do
            {
                t = rand() % 100;
            } while (s.find(t) != s.end());
            s.insert(t);
            a.push_back(t);
        }
        //cout << "Generated: ";
        //for (i = 0; i < n; i++)
        //    cout << a[i] << " ";
        //cout << endl;
        saved = a;

        insertionSort(a, comparison);
        testcaseOutput(saved, a, comparison);
    }

}

void testcaseHeapSort()
{
    vector <int> saved;
    vector <int> a;
    set<int> s;
    int n = 5, i, t, comparison;

    for (int j = 0; j < 100; ++j)
    {
        a.clear();
        s.clear();
        for (i = 0; i < n; ++i)
        {
            do
            {
                t = rand() % 100;
            } while (s.find(t) != s.end());
            s.insert(t);
            a.push_back(t);
        }
        //cout << "Generated: ";
        //for (i = 0; i < n; i++)
        //    cout << a[i] << " ";
        //cout << endl;
        saved = a;

        PSortStart(a, comparison);
        testcaseOutput(saved, a, comparison);
    }

}

void testcaseMergeSort()
{
    vector <int> saved;
    vector <int> a;
    set<int> s;
    int n = 5, i, t, comparison;

    for (int j = 0; j < 100; ++j)
    {
        a.clear();
        s.clear();
        for (i = 0; i < n; ++i)
        {
            do
            {
                t = rand() % 100;
            } while (s.find(t) != s.end());
            s.insert(t);
            a.push_back(t);
        }
        //cout << "Generated: ";
        //for (i = 0; i < n; i++)
        //    cout << a[i] << " ";
        //cout << endl;
        saved = a;

        comparison = 0;

        MergeSort(a, 0, a.size() - 1, comparison);
        testcaseOutput(saved, a, comparison);
    }

}

void testcaseRadixSort()
{
    vector <int> saved;
    vector <int> a;
    set<int> s;
    int n = 5, i, t, comparison;

    for (int j = 0; j < 100; ++j)
    {
        a.clear();
        s.clear();
        for (i = 0; i < n; ++i)
        {
            do
            {
                t = rand() % 100;
            } while (s.find(t) != s.end());
            s.insert(t);
            a.push_back(t);
        }
        //cout << "Generated: ";
        //for (i = 0; i < n; i++)
        //    cout << a[i] << " ";
        //cout << endl;
        saved = a;

        comparison = 0;

        radixsort(a, comparison);
        testcaseOutput(saved, a, comparison);
    }
}

#pragma endregion

int main()
{
    srand(time(NULL));
    vector <int> a;
    set<int> s;
    int n = 5, i, t, sel;

    reenter:
    cout << "1 - Handwritted" << endl << 
        "2 - Random generated" << endl << 
        "3 - testcase with insertion sort(BinSearch)" << endl << 
        "4 - testcase with heap sort" << endl <<
        "5 - testcase with merge sort" << endl <<
        "6 - testcase with radix sort" << endl;
    cout << "Choice: ";
    cin >> sel;

    if (sel == 1)
    {
    start:
        a.clear();
        s.clear();
        cout << "Input " << n << " diff numbers: ";
        for (i = 0; i < n; ++i)
        {
            cout << i + 1 << " number: ";
            cin >> t;
            if (s.find(t) == s.end())
            {
                a.push_back(t);
                s.insert(t);
            }
            else
            {
                cout << "Number was previosly input!" << endl;
                break;
            }
        }
        if (i != n)
            goto start;
    }
    else if (sel == 2)
    {
        a.clear();
        s.clear();
        for (i = 0; i < n; ++i)
        {
            do 
            {
                t = rand() % 100;
            } while (s.find(t) != s.end());
            s.insert(t);
            a.push_back(t);
        }
        cout << "Generated: ";
        for (i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;
    }
    else if (sel == 3)
    {
        testcaseInsertionSort();
        return 0;
    }
    else if (sel == 4)
    {
        testcaseHeapSort();
        return 0;
    }
    else if (sel == 5)
    {
        testcaseMergeSort();
        return 0;
    }
    else if (sel == 6)
    {
        testcaseRadixSort();
        return 0;
    }
    else 
    {
        goto reenter;
    }

    radixsort(a);

    cout << "Sorted array:" << endl;
    for (i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}