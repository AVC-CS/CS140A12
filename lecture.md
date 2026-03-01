# A12. Understanding Unix Memory Structures

## 1. Program vs Process

A **program** is a passive file on disk — your compiled executable (`a.out`).

A **process** is a running instance of that program in memory.

When you type `./a.out`, the OS loader:
- Reads the ELF binary from disk
- Allocates memory and creates 5 segments (TEXT, DATA, BSS, HEAP, STACK)
- Copies machine code into TEXT and initialized data into DATA
- Zeros out BSS, sets up STACK and HEAP pointers
- Jumps to `main()` and execution begins

One program can spawn multiple processes. Each process gets its own isolated memory space.

## 2. The 5 Unix Memory Segments

```
High Address  0x7fffffff

|            |
|   STACK    |   grows down (local vars, function frames)
|     v      |
|            |
|  (free     |
|   space)   |
|            |
|     ^      |
|   HEAP     |   grows up (malloc)
|            |
|   BSS      |   uninitialized globals (zeroed by OS)
|            |
|   DATA     |   initialized globals/statics
|            |
|   TEXT     |   machine code (read-only)
|            |

Low Address   0x00000000
```

### TEXT Segment (Code)
- Contains compiled machine instructions
- Read-only and shared between processes running the same program
- Address of `main()` lives here

```
// TEXT: function addresses
cout << (void*)&main;         // prints a TEXT address
cout << (void*)&checkStack;   // another TEXT address
```

### DATA Segment (Initialized Globals)
- Global and static variables that have initial values
- Read-write

```
int globalVar = 100;        // DATA segment
static int staticVar = 200; // DATA segment
```

### BSS Segment (Uninitialized Globals)
- Global and static variables declared without initial values
- Automatically zeroed by the OS at program start
- Saves space in the executable file (no need to store zeros)

```
int uninitGlobal;   // BSS segment — value is 0
int uninitGlobal2;  // BSS segment — also 0
```

### HEAP Segment (Dynamic Memory)
- Memory allocated at runtime with `malloc`
- Grows **upward** toward higher addresses
- You must free it with `free()` or you leak memory
- Use `malloc` with larger sizes (e.g., 1024) — `new` with small sizes may not allocate sequentially on all platforms

```
char* p1 = (char*)malloc(1024);  // HEAP — first allocation
char* p2 = (char*)malloc(1024);  // HEAP — higher address (heap grows up)
// p2 > p1
```

### STACK Segment (Local Variables)
- Local variables, function parameters, return addresses
- Grows **downward** toward lower addresses
- Automatically managed (created on function entry, destroyed on exit)

**Important**: comparing two local variables within the **same function** does NOT reliably show stack growth — the compiler can reorder variables within a single stack frame.

To demonstrate stack grows down, you must compare across **two function calls**:

```
void checkStack(int* parentAddr) {
    int childVar = 0;
    // parentAddr points to main's local var (parent frame — higher)
    // &childVar is in this function's frame (child frame — lower)
    cout << "Parent frame: " << (void*)parentAddr << endl;
    cout << "Param addr:   " << (void*)&parentAddr << endl;
    cout << "Child local:  " << (void*)&childVar << endl;
    cout << "Stack grows: "
         << (parentAddr > &childVar ? "DOWN" : "UP") << endl;
}

int main() {
    int myVar = 10;
    checkStack(&myVar);  // pass address from parent frame
}
```

The function prints 3 stack addresses:
- `parentAddr` value — points to main's local var (parent frame, higher address)
- `&parentAddr` — parameter's own address (child frame, lower address)
- `&childVar` — local var in child function (child frame, lower address)

Parent frame address is always higher than child frame address — this is guaranteed.

## 3. Walk-through of main.cpp

The demo program `main.cpp` declares variables in all 5 segments and prints their addresses:

**Global scope (before main):**
- `int globalVar = 100;` — DATA segment (initialized global)
- `static int staticVar = 200;` — DATA segment (static initialized)
- `int uninitGlobal;` — BSS segment (uninitialized global)
- `int uninitGlobal2;` — BSS segment (second uninitialized global)

**checkStack() function:**
- Receives address of main's local variable (parent frame)
- Declares its own local variable (child frame)
- Prints 3 addresses: parent value, parameter address, child local address
- Compares parent vs child frame to prove stack grows DOWN

**Inside main():**
- `int mainVar = 10;` — STACK segment (local variable, passed to checkStack)
- `char* heapVar1 = (char*)malloc(1024)` — HEAP segment
- `char* heapVar2 = (char*)malloc(1024)` — HEAP segment (higher address)

**Output shows:**
- TEXT addresses are the lowest (code lives at bottom)
- DATA and BSS are above TEXT
- HEAP addresses are above BSS and grow upward (heapVar2 > heapVar1)
- STACK addresses are the highest and grow downward (parent frame > child frame)

This matches the memory layout diagram exactly.

## 4. Student Activity

Fill in the skeleton `main.cpp` to demonstrate all 5 memory segments:

- Declare at least 2 initialized globals (DATA)
- Declare at least 2 uninitialized globals (BSS)
- Declare a local variable in main and pass its address to `checkStack()` (STACK)
- `checkStack()` is provided — it prints 3 stack addresses (parent local, param, child local) and the growth direction
- Allocate at least 2 heap variables with `malloc` using larger sizes like 1024 (HEAP)
- Print 2 function addresses: `main` and `checkStack` (TEXT)
- Print all addresses with segment labels
- Print `Heap grows: UP` or `DOWN` based on comparing the two heap addresses
- Free all heap allocations with `free()`
- Write experimental results as a comment block at the bottom of your `main.cpp`
- Run: `./a.out > result.txt`

### How to compile and test
```
g++ -std=c++17 -Wall -Wextra main.cpp -o a.out
./a.out > result.txt
pytest -rP
```

### Grading (100 pts total)
- Compile (20 pts): compiles with `-Wall -Wextra`
- T1 (20 pts): `result.txt` contains all 5 segment labels (TEXT, DATA, BSS, STACK, HEAP)
- T2 (20 pts): `result.txt` contains at least 2 hex addresses per segment (3 for STACK)
- T3 (20 pts): output shows `Stack grows: DOWN` (cross-function comparison)
- T4 (20 pts): output shows `Heap grows: UP` (sequential malloc comparison)
