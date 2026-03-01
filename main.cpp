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

/*
 * ============================================================
 * TROUBLESHOOTING — if your test fails, check here first
 * ============================================================
 *
 * STEP 1: compile and save output
 *   g++ main.cpp
 *   ./a.out > result.txt
 *   (you must run both commands every time you change main.cpp)
 *
 * ------------------------------------------------------------
 * T1 or T2 fails — "Missing: TEXT1" (or any key)
 *
 *   Each output line must have exactly TWO things:
 *     1. the label  (e.g. TEXT1)
 *     2. the address (e.g. 0x100001234)
 *
 *     TEXT1   0x100001234   <-- correct
 *     TEXT2   0x100001568   <-- correct (TEXT2 address is higher than TEXT1)
 *
 *   The test compares these two: label on the left, address on the right.
 *   If you add extra words, or print them on separate lines, the test
 *   cannot match the label to its address and will report it missing.
 *   Do NOT delete the cout << "TEXT1\t"; line.
 *
 * ------------------------------------------------------------
 * T2 fails — "Missing: STACK2" or "Missing: STACK3"
 *
 *   You forgot to call checkStack().
 *   After printing STACK1, add this line:
 *     checkStack((void*)&myVar);
 *   checkStack() prints STACK2 and STACK3 automatically.
 *
 *   Your complete result.txt should look like this
 *   (your addresses will be different, but the ORDER must match):
 *
 *     TEXT1   0x100001234   <- TEXT grows up
 *     TEXT2   0x100001568   <- TEXT2 > TEXT1
 *     DATA1   0x100010000   <- DATA grows up
 *     DATA2   0x100010004   <- DATA2 > DATA1
 *     BSS1    0x100010008   <- BSS grows up
 *     BSS2    0x10001000c   <- BSS2 > BSS1
 *     STACK1  0x16fb4e3f8   <- STACK grows DOWN
 *     STACK2  0x16fb4e3a8   <- STACK2 < STACK1
 *     STACK3  0x16fb4e3a4   <- STACK3 < STACK2
 *     HEAP1   0x600000abc   <- HEAP grows up
 *     HEAP2   0x600000ebc   <- HEAP2 > HEAP1
 *
 * ------------------------------------------------------------
 * T3 fails — "STACK1 should be > STACK3"
 *
 *   Make sure the variable you pass to checkStack() is declared
 *   INSIDE main(), not outside (not a global).
 *   Example:
 *     int myVar = 10;           // declared inside main()
 *     checkStack((void*)&myVar);
 *
 * ------------------------------------------------------------
 * T4 fails — "HEAP1 should be < HEAP2"
 *
 *   Use malloc(1024), not new.
 *   Make sure h1 and h2 are two different variables:
 *     char* h1 = (char*)malloc(1024);
 *     char* h2 = (char*)malloc(1024);
 *
 * ------------------------------------------------------------
 * HEAP lines are blank in result.txt
 *
 *   h1 and h2 are char* — cout treats them as text, not address.
 *   You must cast to void*:
 *     cout << (void*)h1 << endl;   // correct
 *     cout << h1 << endl;          // WRONG — prints nothing
 *
 * ============================================================
 */
