import pytest
import os


def load_result():
    assert os.path.exists('result.txt'), \
        "result.txt not found — run: ./a.out > result.txt"
    with open('result.txt') as f:
        return f.read()


def parse(content):
    """Parse structured output into {LABEL: [addresses]}.
    Each line must start with a segment label followed by hex addresses:
        TEXT 0x... 0x...
        STACK 0x... 0x... 0x...
    """
    LABELS = {'TEXT', 'DATA', 'BSS', 'STACK', 'HEAP'}
    result = {}
    for line in content.splitlines():
        tokens = line.split()
        if tokens and tokens[0] in LABELS:
            result[tokens[0]] = [int(t, 16) for t in tokens[1:]]
    return result


@pytest.fixture
def segments():
    return parse(load_result())


@pytest.mark.T1
def test_segment_labels(segments):
    """T1: all 5 segment labels present in output"""
    for label in ['TEXT', 'DATA', 'BSS', 'STACK', 'HEAP']:
        assert label in segments, f"Missing segment: {label}"


@pytest.mark.T2
def test_hex_addresses(segments):
    """T2: each segment has at least 2 addresses"""
    for label in ['TEXT', 'DATA', 'BSS', 'STACK', 'HEAP']:
        addrs = segments.get(label, [])
        assert len(addrs) >= 2, \
            f"{label}: need 2+ addresses, got {len(addrs)}"


@pytest.mark.T3
def test_stack_grows_down(segments):
    """T3: stack grows down — parent frame address > child frame address"""
    addrs = segments.get('STACK', [])
    assert len(addrs) >= 3, \
        f"STACK: need 3 addresses (parent, param, child), got {len(addrs)}"
    assert addrs[0] > addrs[2], \
        f"Stack should grow down: parent {hex(addrs[0])} > child {hex(addrs[2])}"


@pytest.mark.T4
def test_heap_grows_up(segments):
    """T4: heap grows up — first allocation address < second allocation address"""
    addrs = segments.get('HEAP', [])
    assert len(addrs) >= 2, \
        f"HEAP: need 2 addresses, got {len(addrs)}"
    assert addrs[0] < addrs[1], \
        f"Heap should grow up: first {hex(addrs[0])} < second {hex(addrs[1])}"
