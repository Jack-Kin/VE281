//
//  lab3.cpp
//  
//
//  Created by kitatine on 2019/10/11.
//
//

#include "lab3.hpp"

void swap(long long& A, long long& B){
    // MODIFIES: A, B
    // EFFECTS: swap the content stored in A and B
    long long tmp=A;
    A=B;
    B=tmp;
}

long long LinearSearch(long long* A, long long N, long long i,long long left,long long right){
    // EFFECTS: return the first index of the element whose content is i contained in the array A
    //    cout << "Before Search the Array is " << endl;
    //    PrintArrayLR(A,left,right);
    for (long long j = left; j <= right; j++){
        if (A[j] == i) return j;
    }
    return 0;
}

long long Partition(long long *A,long long left,long long right,bool sel,long long cpivot){
    // MODIFIES:
    // EFFECTS:
    long long pivotat;
    long long size = right - left + 1;

    if (size==2){
        if (A[left] >=A[right]){swap(A[left],A[right]);}
        return right;
    }
    
    if(sel == 1){
        srand((unsigned int) time(nullptr));
        pivotat = left + rand()%size;}
    else {
        pivotat = cpivot;
    }

    swap (A[left],A[pivotat]);
    long long i = left+1 , j = right;
    bool flag = (i<j);
    while(flag) {
        while (i <= right && A[i] < A[left]) {
            i++;
        }
        while (j > left && A[j] >= A[left]) {
            j--;
        }
        if(i<j){swap(A[i],A[j]);continue;}
        else flag=false;
    }
    swap(A[left],A[j]);

    return j;
}


long long* ChoosePivot(long long*A, long long left,long long right){
    long long size = right - left + 1;
    long long nums = size%5 ? size/5+1 : size/5 ;
    long long i =left,j=0;
    auto *C = new long long [nums*sizeof(long long)];
    while (i<=right){
        if(i+5<=right){
            QuickSort(A,i,i+4);
            C[j++] = A[i+2]; }
        else{
            QuickSort(A,i,right);
            C[j] = A[(i+right)/2];
            break;
        }
        i+=5;
    }
    return C;
}



long long Dselect(long long*A, long long left, long long right, long long i){
    long long n = right - left + 1;
    long long size = n%5 ? n/5+1 : n/5 ;
    if (n==1){return A[left];}

    //Choose Pivot
    long long pivot;
    long long* C = ChoosePivot(A,left,right);
    pivot=Dselect(C,0,size-1,(size-1)/2);
    
    long long pivotat = LinearSearch(A,n,pivot,left,right);

    //Partition
    pivotat = Partition(A,left,right,false,pivotat);
    
    //The common Part with Rselect
    
    delete []C;
    
    if(pivotat-left == i){
        //        cout << "Chosen Pivot" << endl;
        return A[pivotat];
    }
    if(pivotat-left > i){
        //        cout << "Chosen left" << endl;
        return Dselect(A,left,pivotat-1,i);
    }
    else {
        //        cout << "Chosen Right" << endl;
        
        //Relative pivotat = pivotat-left+1
        return Dselect(A, pivotat+1, right, i - (pivotat-left+1));
    }
}
