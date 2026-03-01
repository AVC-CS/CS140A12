import pytest
import os


def load_result():
    assert os.path.exists('result.txt'), \
        "result.txt not found — run: ./a.out > result.txt"
    with open('result.txt') as f:
        return f.read()


def parse(content):
    """Parse 'KEY<tab>ADDRESS' lines into {KEY: int address}."""
    result = {}
    for line in content.splitlines():
        parts = line.split()
        if len(parts) == 2:
            try:
                result[parts[0]] = int(parts[1], 16)
            except ValueError:
                pass
    return result


@pytest.fixture
def data():
    return parse(load_result())


@pytest.mark.T1
def test_segment_labels(data):
    """T1: at least one address per segment"""
    for key in ['TEXT1', 'DATA1', 'BSS1', 'STACK1', 'HEAP1']:
        assert key in data, f"Missing: {key}"


@pytest.mark.T2
def test_all_addresses(data):
    """T2: all required addresses present"""
    for key in ['TEXT1', 'TEXT2', 'DATA1', 'DATA2', 'BSS1', 'BSS2',
                'STACK1', 'STACK2', 'STACK3', 'HEAP1', 'HEAP2']:
        assert key in data, f"Missing: {key}"


@pytest.mark.T3
def test_stack_grows_down(data):
    """T3: STACK1 (main local) > STACK3 (child local) — stack grows down"""
    assert data['STACK1'] > data['STACK3'], \
        f"Stack grows down: STACK1 {hex(data['STACK1'])} should be > STACK3 {hex(data['STACK3'])}"


@pytest.mark.T4
def test_heap_grows_up(data):
    """T4: HEAP1 < HEAP2 — heap grows up"""
    assert data['HEAP1'] < data['HEAP2'], \
        f"Heap grows up: HEAP1 {hex(data['HEAP1'])} should be < HEAP2 {hex(data['HEAP2'])}"
