# CS140 A12 — Understanding Unix Memory Segments

Edit **`main.cpp`** only. Print the address of something from each memory segment, then read the
addresses and see where each segment lives.

## Work through the file top to bottom — six sections, six commits

`main.cpp` is already laid out in six numbered sections. Finish one section, check it, commit it,
push it. Then start the next. **Do not do all six and commit once.**

| Section | What you fill in | Commit message |
|---|---|---|
| 1 | two initialized globals, two uninitialized globals | `section 1: globals (data + bss)` |
| 2 | `TEXT1`, `TEXT2` — the addresses of two functions | `section 2: TEXT addresses` |
| 3 | `DATA1`, `DATA2` — the initialized globals | `section 3: DATA addresses` |
| 4 | `BSS1`, `BSS2` — the uninitialized globals | `section 4: BSS addresses` |
| 5 | a local in `main`, `STACK1`, then call `checkStack` | `section 5: STACK addresses` |
| 6 | two `malloc` blocks, `HEAP1`, `HEAP2`, then `free` | `section 6: HEAP addresses` |

After each section:

```
g++ main.cpp
```
```
./a.out > result.txt
```
```
git add main.cpp
```
```
git commit -m "section 2: TEXT addresses"
```
```
git push
```

Sections 1 to 4 will not pass the tests on their own — that is expected. The tests need every
label, so they go green only after section 6. Commit anyway: the point of committing each section
is that your history shows the program being built up one segment at a time.

## Do not touch

- The `checkStack` function at the top. It is the template's, and it prints `STACK2` and `STACK3`.
- Any `cout << "LABEL\t";` line. Deleting one makes the test report that label missing.
- `main_test.py`, `pytest.ini`, `data/run.sh`, anything under `.github/`.

## Compile

```
g++ -std=c++17 -Wall -Wextra main.cpp -o a.out
```

## Run

```
./a.out > result.txt
```

## Test

```
data/run.sh
```
```
pytest -rP
```

Read the TROUBLESHOOTING block at the bottom of `main.cpp` before asking — it names the usual
failures and the exact fix for each.
