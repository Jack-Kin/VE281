#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>

using namespace std;

void swap(int a[], int i, int j ){
    int temp =  a[i];
    a[i] = a[j];
    a[j] = temp;
}

void BubbleSort(int a[],int n){
    int i  = 0;
    bool sorted = false;
    while( i < n-1 && !sorted){
        sorted = true;
        for ( int j = n - 1;  j >  i; j--){
            if(a[j] < a[j-1]){
                swap(a, j, j-1);
                sorted = false;
            }
//            if (sorted){break;}
        }
        i++;
    }
}

void InsertionSort(int a[], int n){
    int i, j;
    for ( j = 1; j <= n - 1 ; ++j) {
        int key = a[j];
        i = j - 1;
        while (i >= 0 && a[i] > key){
            a[i+1] = a[i];
            i--;
        }
        a[i+1]= key;
    }
}

void SelectionSort(int a[], int n){
    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i+1; j < n; ++j) {
            if (a[j] < a[minIndex]){
                minIndex = j;
            }
        }
        swap(a, i, minIndex);
    }
}


void Merge(int a[], int left, int mid, int right){
    if (right <= left) return;
    int len_L = mid - left + 1 + 1;
    int len_R = right - mid + 1;
    int * L = new int[len_L];
    int *R = new int[len_R];
//    int L[len_L];
//    int R[len_R];
    for (int i = 0; i < len_L - 1; ++i) {
        L[i] = a[left + i];
    }
    for (int j = 0; j < len_R - 1; ++j) {
        R[j] = a[mid + 1 + j];
    }
    L[len_L-1] = INT_MAX;
    R[len_R-1] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k = left; k <= right ; ++k) {
        if (L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
    }
    delete [] L;
    delete [] R;
}


void MergeSort(int a[], int left, int right){
    if (left >= right) return;
    int mid = (left + right)/2;
    MergeSort(a, left, mid);
    MergeSort(a, mid+1, right);
    Merge(a, left, mid, right);
}

int partition(int a[], int left, int right){
    //randomly choose a pivot
    int pivot_pos = rand()%(right - left +1) + left;
//    cout << "pivot pos  is : " << pivot_pos << endl;
    int pivot = a[pivot_pos];
    swap(a, left, pivot_pos);
    int i = left+1;
    int j = right;
    if (i == j){
        if (a[left] > a[right]){swap(a,left,right);}
        return j;
    }
    while (i < j){
        while (i < right  && a[i] < pivot){
            i++;
        }
        while (j > left && a[j] >= pivot){
            j--;
        }
        if (i < j) {swap(a, i, j);}
    }
    swap(a,left,j);
    return j;
}

void QuickSort(int a[], int left, int right) {
    int pivotat;
    if (left >= right) return;
    pivotat = partition(a, left, right);
    QuickSort(a, left, pivotat -1);
    QuickSort(a, pivotat+1, right);
}


int Rselect(int a[], int start, int end, int i){
    //find i th smallest item of array of size n
    int n = end - start +1;
//    cout << "find the " << i << " th smallest item of array from index" << start << " to " << end << endl;
    if (n <= 1) return a[start];
    if (n == 2 && i == 1){
        if (a[start] < a[end]) return a[start];
        else return a[end];
    }
    if (n == 2 && i == 2){
        if (a[start] > a[end]) return a[start];
        else return a[end];
    }

    int pivotat;
    pivotat = partition(a, start,  end);
    int pivot = a[pivotat];
    int index_i = i -1;
    if  (pivotat - start == index_i) return pivot;
    if (pivotat - start > index_i){
        return Rselect(a, start, start + pivotat-start -1, i);
    }
    else{
        return Rselect(a, end +2 + (pivotat-start) - n, end, i - (pivotat-start+1));
    }
}

int partition(int a[], int left, int right, int pivotat) {
//    int pivotat;
    int size = right - left + 1;
    if (size==2){
        if (a[left] >=a[right]){swap(a[left],a[right]);}
        return right;
    }
    swap (a[left],a[pivotat]);
    int i = left + 1;
    int j = right;
    bool flag = (i<j);
    while(flag) {
        while (i <= right && a[i] < a[left]) {
            i++;
        }
        while (j > left && a[j] >= a[left]) {
            j--;
        }
        if(i<j){swap(a[i],a[j]);continue;}
        else flag=false;
    }
    swap(a[left],a[j]);
    return j;

}



int Dselect(int a[], int left, int right, int i){
    int n = right - left + 1;
    int size =  n%5 ? n/5+1 : n/5;
    if ( n == 1) return a[left];

    // Choose pivot
    int *C = new int[size * sizeof(int)];
    int ii = left;
    int j = 0;
    while (ii<=right){
        if(ii+5<=right){
            QuickSort(a,ii,ii+4);
            C[j++] = a[ii+2]; }
        else{
            QuickSort(a,ii,right);
            C[j] = a[(ii+right)/2];
            break;
        }
        ii+=5;
    }

    int pivot;pivot=Dselect(C,0,size-1,(size-1)/2);

    int pivotat = 0;
    bool FIND = false;
    for (int k = left; k <= right ; ++k) {
        if (a[k] == pivot) {
            pivotat = k;
            FIND = true;
            break;
        }
    }
    if (!FIND) pivotat = 0;
    pivotat = partition(a,left,right,pivotat);

    delete []C;

    if(pivotat-left == i){
        return a[pivotat];
    }
    if(pivotat-left > i){
        return Dselect(a,left,pivotat-1,i);
    }
    else {
        return Dselect(a, pivotat+1, right, i - (pivotat-left+1));
    }

}



//int Dselect(int a[], int start, int end, int i){
//    //find i th smallest item of array of size n
//    int n = end - start +1;
////    cout << "find the " << i << " th smallest item of array from index" << start << " to " << end << endl;
//    if (n <= 1) return a[start];
//    if (n == 2 && i == 1){
//        if (a[start] < a[end]) return a[start];
//        else return a[end];
//    }
//    if (n == 2 && i == 2){
//        if (a[start] > a[end]) return a[start];
//        else return a[end];
//    }
//
//    //break a into 5 groups, sort each group
//    int ij = start;
//    while (ij <= end){
//        if (end - ij <5){
//            QuickSort(a, ij, end);
//        }
//        else QuickSort(a, ij, ij+4);
//        ij = ij + 5;
//    }
//
//    //create C, containg n/5 + 1 medians
//    int size = n%5 ? n/5+1 : n/5;
//    //TODO: why the size of C cannot be greater than 5?
//    int* C = new int [size];
////    int C[C_size];
//    for (int k = 0; k < size; k ++) {
//        if (k != size -1){
//            C[k] = a[5*k + 2];
//        }
//        else {
//            int num = (end - 5*k)/2 ;
//            C[k] = a[5*k + num];
//        }
//    }
//
//    //p = Dselect(C, n/5, n/10);
//    int pivot = Dselect(C, 0, size-1 , (size-1)/2 );
//    delete [] C;
//
//    //Partition A using pivot p;
//    //Let pivotat be the index of pivot;
//    int pivotat;
//    pivotat = partition(a, start,  end, pivot);
//
//    //do recursion
//    int index_i = i -1;
//    if  (pivotat - start == index_i) return pivot;
//    if (pivotat - start > index_i){
//        return Dselect(a, start, start + pivotat-start -1, i);
//    }
//    else{
//        return Dselect(a, end +2 + (pivotat-start) - n, end, i - (pivotat-start+1));
//    }
//}
//



int main() {
//    srand((unsigned)time(NULL));
//    int N = 50000;
//    int arr[N];
//    int tem[N];
//    int avgN = 20;
//    int data[avgN];
//    int random[avgN];
//    for (int l = 0; l < avgN; ++l) {
//        random[l] = rand()%N;
//    }
//
//    for (int i = 0; i < N; i++)
//    {
//        cin >> arr[i];
//    }
//    //Let tem = arr
//    for (int j = 0; j < N; ++j) {
//        tem[N] = arr[N];
//    }
//
//
//    for (int j = 0; j < avgN; ++j) {
//        //give value back to arr
//        for (int j = 0; j < N; ++j) {
//            arr[N] = tem[N];
//        }
//        //begin clock
//        clock_t t;
//        t = clock();
//        Dselect(arr, 0, N-1, random[j]);
////        QuickSort(arr, 0, N-1);
//        t = clock() - t;
//        data[j] = t;
//    }
//    int sum = 0;
//    for (int k = 0; k < avgN; ++k) {
//        sum = sum + data[k];
//    }
//    int avg = sum / avgN;
////    clock_t t;
////    t = clock();
//////    BubbleSort(arr, N);
//////    InsertionSort(arr, N);
//////    SelectionSort(arr, N);
//////    MergeSort(arr, 0, N-1);
////    QuickSort(arr, 0, N-1);
//////    Rselect(arr, 0, N-1, ith);
//////    Dselect(arr, 0, N-1, ith);
////    t = clock() - t;
//    printf ("It takes (%f seconds).\n",(float)avg/CLOCKS_PER_SEC);
////    printf ("It takes (%f seconds).\n",((float)t)/CLOCKS_PER_SEC);
//


    int mode, N;
    int num;
    cin >> mode;
    cin >> N;
    int ith = 0;
    if (mode >= 5){cin >> ith;}
    ith +=1;
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    switch (mode){
        case 0 :
            BubbleSort(arr,N);
            for (int i = 0; i < N; i++){cout << arr[i] << endl;}
            break;
        case 1 :
            InsertionSort(arr, N);
            for (int i = 0; i < N; i++){cout << arr[i] << endl;}
            break;
        case 2 :
            SelectionSort(arr, N);
            for (int i = 0; i < N; i++){cout << arr[i] << endl;}
            break;
        case 3 :
            MergeSort(arr, 0, N-1);
            for (int i = 0; i < N; i++){cout << arr[i] << endl;}
            break;
        case 4 :
            QuickSort(arr, 0, N-1);
            for (int i = 0; i < N; i++){cout << arr[i] << endl;}
            break;
        case 5 :
            num =  Rselect(arr, 0, N-1, ith);
            cout << "The order-" << ith-1 << " item is " << num << endl;
            break;
        case 6 :
            ith -=1;
            num = Dselect(arr, 0, N-1, ith);
            cout << "The order-" << ith << " item is " << num << endl;
            break;
    }



    return 0;
}
