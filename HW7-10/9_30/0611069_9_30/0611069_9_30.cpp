//worst case: small to large
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include "0611069_9_30.h"
using namespace std;

int compare(void* a,void* b){
    return *(int*)a - *(int*)b;
}

int main()
{
    HEAP* heap;
    int size[5] = {100,200,500,1000,2000};  //array size
    srand((unsigned)time(nullptr));   //set random seed
    int* testdata;
    int data[5];
    int sum = 0;
    double avg = 0;
    int total_size=0;
    HEAP* heaparr[5];
    cout<<"heap up (insert node): "<<endl;
    for(int i=0;i<5;i++){
        heap = heapCreate(2000,compare);    //create a new heap for each test
        for(int j=0;j<size[i];j++){
            testdata = new int;
            *testdata = j;  //form 0 to size[i]-1, would be worst case
            heapInsert(heap,testdata,&sum);
        }
        cout<<"array size = "<<setw(5)<<size[i]<<":  "<<setw(5)<<sum<<" steps\t";
        cout<<setw(4)<<"(steps/size = "<<fixed<<setprecision(2)<<(double)sum/size[i]<<")"<<endl;
        avg+=((double)sum/size[i]);
        sum = 0;
        heaparr[i] = heap;
    }
    avg/=5;
    cout<<"The efficiency of building a heap in Big-O notation is n (about "<<setprecision(0)<<avg<<"n)"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"heap sown (delete root): "<<endl;
    void* dataOut;
    avg = 0;
    for(int i=0;i<5;i++){
            heap = heaparr[i];
        for(int j=0;j<size[i];j++){
            dataOut = heap->heapAry[0];
            heapDelete(heap,(void**)dataOut,&sum);
        }
        cout<<"array size = "<<setw(5)<<size[i]<<":  "<<setw(5)<<sum<<" steps\t";
        cout<<setw(4)<<"(steps/size = "<<fixed<<setprecision(2)<<(double)sum/size[i]<<")"<<endl;
        avg += ((double)sum/size[i]);
        sum = 0;
    }
    avg/=5;
    cout<<"The efficiency of building a heap in Big-O notation is n (about "<<setprecision(0)<<avg<<"n)"<<endl;
    cout<<"========================================="<<endl;

    return 0;
}
