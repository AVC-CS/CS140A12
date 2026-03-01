#include <iostream>
#include <cstdlib>
using namespace std;

// Template: do not modify
// Prints STACK2 (param address) and STACK3 (child local address)
void checkStack(void* parentAddr) {
    int childVar = 0;
    cout << "STACK2\t" << (void*)&parentAddr << endl;
    cout << "STACK3\t" << (void*)&childVar   << endl;
}

/*********************************************
 * TODO: declare 2 initialized globals here
 *       int myGlobal1 = 10;
 *       int myGlobal2 = 20;
 *
 * TODO: declare 2 uninitialized globals here
 *       int myBss1;
 *       int myBss2;
 *********************************************/
int globalVar1 = 10;
int globalVar2 = 20;
int bssVar1;
int bssVar2;


int main() {

    /* Do not delete below cout
    ***************************/
    cout << "TEXT1\t";
    /***********************************
     * Print address of a function:
     *   cout << (void*)&functionName << endl;
     ***********************************/
    cout << (void*)&main << endl;

    /* Do not delete below cout
    ***************************/
    cout << "TEXT2\t";
    /***********************************
     * Print address of a function:
     *   cout << (void*)&functionName << endl;
     ***********************************/
    cout << (void*)&checkStack << endl;


    /* Do not delete below cout
    ***************************/
    cout << "DATA1\t";
    /***********************************
     * Print address of an initialized global:
     *   cout << (void*)&myGlobal1 << endl;
     ***********************************/
    cout << (void*)&globalVar1 << endl;

    /* Do not delete below cout
    ***************************/
    cout << "DATA2\t";
    /***********************************
     * Print address of an initialized global:
     *   cout << (void*)&myGlobal2 << endl;
     ***********************************/
    cout << (void*)&globalVar2 << endl;


    /* Do not delete below cout
    ***************************/
    cout << "BSS1\t";
    /***********************************
     * Print address of an uninitialized global:
     *   cout << (void*)&myBss1 << endl;
     ***********************************/
    cout << (void*)&bssVar1 << endl;

    /* Do not delete below cout
    ***************************/
    cout << "BSS2\t";
    /***********************************
     * Print address of an uninitialized global:
     *   cout << (void*)&myBss2 << endl;
     ***********************************/
    cout << (void*)&bssVar2 << endl;


    /***********************************
     * Declare a local variable in main:
     *   int myVar = 10;
     ***********************************/
    int myVar = 10;

    /* Do not delete below cout
    ***************************/
    cout << "STACK1\t";
    /***********************************
     * Print address of your local variable:
     *   cout << (void*)&myVar << endl;
     *
     * Then call checkStack — it prints STACK2 and STACK3:
     *   checkStack((void*)&myVar);
     ***********************************/
    cout << (void*)&myVar << endl;
    checkStack((void*)&myVar);


    /***********************************
     * Allocate 2 heap blocks:
     *   char* h1 = (char*)malloc(1024);
     *   char* h2 = (char*)malloc(1024);
     ***********************************/
    char* h1 = (char*)malloc(1024);
    char* h2 = (char*)malloc(1024);

    /* Do not delete below cout
    ***************************/
    cout << "HEAP1\t";
    /***********************************
     * Print address of first heap block:
     *   cout << (void*)h1 << endl;
     ***********************************/
    cout << (void*)h1 << endl;

    /* Do not delete below cout
    ***************************/
    cout << "HEAP2\t";
    /***********************************
     * Print address of second heap block:
     *   cout << (void*)h2 << endl;
     *
     * Then free both:
     *   free(h1);
     *   free(h2);
     ***********************************/
    cout << (void*)h2 << endl;
    free(h1);
    free(h2);

    return 0;
}
