#!/usr/bin/env python

import ctypes
ffi = ctypes.CDLL('./ffi-c.so')
print "hello ",
ffi.hello("world")

ffi.sinc.argtypes = [ctypes.c_double]
ffi.sinc.restype = ctypes.c_double
print ffi.sinc(1.0)
