#include <iostream>
#include <cstdlib>  // for malloc
using namespace std;

// TEXT segment - code lives here (functions)
// DATA segment - global/static initialized variables
int globalVar = 100;           // initialized data (DATA)
static int staticVar = 200;    // static initialized (DATA)

// BSS segment (uninitialized data, part of DATA)
int uninitGlobal;              // uninitialized global (BSS)

int main() {

    // STACK segment - local variables
    int stackVar1 = 10;
    int stackVar2 = 20;
    char stackArr[64];

    // HEAP segment - dynamic allocation
    int* heapVar1 = new int(42);
    int* heapVar2 = (int*)malloc(sizeof(int));
    *heapVar2 = 99;

    cout << "=== MEMORY SEGMENT BOUNDARIES ===" << endl;
    cout << endl;

    // TEXT segment (code/instructions)
    cout << "--- TEXT SEGMENT (Code) ---" << endl;
    cout << "Address of main()      : " << (void*)&main << endl;
    cout << "Address of a function  : " << (void*)&exit << endl;
    cout << endl;

    // DATA segment (initialized globals)
    cout << "--- DATA SEGMENT (Initialized Globals) ---" << endl;
    cout << "globalVar  addr : " << (void*)&globalVar  
         << " value: " << globalVar << endl;
    cout << "staticVar  addr : " << (void*)&staticVar  
         << " value: " << staticVar << endl;
    cout << endl;

    // BSS segment (uninitialized globals)
    cout << "--- BSS SEGMENT (Uninitialized Globals) ---" << endl;
    cout << "uninitGlobal addr: " << (void*)&uninitGlobal 
         << " value: " << uninitGlobal << endl;
    cout << endl;

    // STACK segment (local variables - grows DOWN)
    cout << "--- STACK SEGMENT (Local Variables) ---" << endl;
    cout << "stackVar1 addr : " << (void*)&stackVar1 << endl;
    cout << "stackVar2 addr : " << (void*)&stackVar2 << endl;
    cout << "stackArr  addr : " << (void*)&stackArr  << endl;
    cout << "Stack grows: " 
         << (&stackVar1 > &stackVar2 ? "DOWN (higher→lower)" : "UP") 
         << endl;
    cout << endl;

    // HEAP segment (dynamic - grows UP)
    cout << "--- HEAP SEGMENT (Dynamic Allocation) ---" << endl;
    cout << "heapVar1 addr  : " << (void*)heapVar1 << endl;
    cout << "heapVar2 addr  : " << (void*)heapVar2 << endl;
    cout << "Heap grows: "
         << (heapVar2 > heapVar1 ? "UP (lower→higher)" : "DOWN")
         << endl;
    cout << endl;

    // Summary - relative positions
    cout << "=== RELATIVE POSITION SUMMARY ===" << endl;
    cout << "TEXT  (lowest) : " << (void*)&main      << endl;
    cout << "DATA           : " << (void*)&globalVar  << endl;
    cout << "BSS            : " << (void*)&uninitGlobal << endl;
    cout << "HEAP           : " << (void*)heapVar1   << endl;
    cout << "STACK (highest): " << (void*)&stackVar1 << endl;

    // cleanup
    delete heapVar1;
    free(heapVar2);

    return 0;
}