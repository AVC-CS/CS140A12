import pytest
import os
import re


def load_result():
    """Load result.txt and return its content."""
    assert os.path.exists('result.txt'), \
        "result.txt not found — run: ./a.out > result.txt"
    with open('result.txt', 'r') as f:
        return f.read()


def extract_addresses(content, label):
    """Find all hex addresses on lines containing the label (case-insensitive)."""
    addrs = []
    for line in content.split('\n'):
        if label.lower() in line.lower():
            found = re.findall(r'0x[0-9a-fA-F]+', line)
            addrs.extend(found)
    return [int(a, 16) for a in addrs]


@pytest.mark.T1
def test_segment_labels():
    """T1: result.txt contains all 5 segment labels"""
    content = load_result()
    print(f"Output length: {len(content)} chars")

    for label in ['TEXT', 'DATA', 'BSS', 'STACK', 'HEAP']:
        found = label.lower() in content.lower()
        assert found, f"Missing segment label: {label}"
        print(f"PASS: found '{label}' in output")

    print("PASS: all 5 segment labels present")


@pytest.mark.T2
def test_hex_addresses():
    """T2: result.txt contains at least 2 hex addresses per segment"""
    content = load_result()

    for label in ['TEXT', 'DATA', 'BSS', 'STACK', 'HEAP']:
        addrs = extract_addresses(content, label)
        assert len(addrs) >= 2, \
            f"{label}: expected at least 2 hex addresses, found {len(addrs)}"
        print(f"PASS: {label} has {len(addrs)} addresses: {[hex(a) for a in addrs]}")

    print("PASS: all segments have at least 2 hex addresses")


@pytest.mark.T3
def test_stack_grows_down():
    """T3: stack addresses decrease (first declared > second declared)"""
    content = load_result()
    addrs = extract_addresses(content, 'STACK')
    assert len(addrs) >= 2, \
        f"STACK: need at least 2 addresses, found {len(addrs)}"

    first, second = addrs[0], addrs[1]
    print(f"Stack addr1: {hex(first)}")
    print(f"Stack addr2: {hex(second)}")
    assert first > second, \
        f"Stack should grow DOWN: first ({hex(first)}) should be > second ({hex(second)})"
    print("PASS: stack grows down (first address > second address)")


@pytest.mark.T4
def test_heap_grows_up():
    """T4: heap addresses increase (second allocation > first allocation)"""
    content = load_result()
    addrs = extract_addresses(content, 'HEAP')
    assert len(addrs) >= 2, \
        f"HEAP: need at least 2 addresses, found {len(addrs)}"

    first, second = addrs[0], addrs[1]
    print(f"Heap addr1: {hex(first)}")
    print(f"Heap addr2: {hex(second)}")
    assert second > first, \
        f"Heap should grow UP: second ({hex(second)}) should be > first ({hex(first)})"
    print("PASS: heap grows up (second address > first address)")
