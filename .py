#!/usr/bin/python3
import sys

def hash_(n):
    khash = 0
    for i in n:
        khash *= 281474976710677
        khash ^= ord(i) | ord(i) << 32
    khash &= 0xffffffffffffffff
    return khash

print(hash_(sys.argv[1]))
