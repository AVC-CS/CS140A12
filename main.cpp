#include <iostream>
#include <cstdlib>
using namespace std;

// ── Template-provided functions (do not modify) ──────────────────────────────

// Outputs one structured line: LABEL addr1 addr2 ...
void report(const char* label, void* addrs[], int n) {
    cout << label;
    for (int i = 0; i < n; i++) cout << " " << addrs[i];
    cout << endl;
}

// Captures 3 stack addresses into out[]:
//   out[0] = parentAddr value  (parent frame — passed from main)
//   out[1] = &parentAddr       (param lives in child frame)
//   out[2] = &childVar         (local lives in child frame)
void checkStack(void* parentAddr, void* out[]) {
    int childVar = 0;
    out[0] = parentAddr;
    out[1] = (void*)&parentAddr;
    out[2] = (void*)&childVar;
}

// ── Student: declare globals below ───────────────────────────────────────────

// TODO: declare 2 initialized global variables   (DATA segment)

// TODO: declare 2 uninitialized global variables (BSS segment)

// ── Student: complete main() below ───────────────────────────────────────────

int main() {

    // TEXT: report 2 function addresses
    // TODO

    // DATA: report 2 initialized global addresses
    // TODO

    // BSS: report 2 uninitialized global addresses
    // TODO

    // STACK: declare a local var, capture stack addresses, report
    // TODO

    // HEAP: allocate 2 blocks with malloc(1024), report, then free
    // TODO

    return 0;
}
