#!/usr/bin/python3.5
# -*- coding: utf-8 -*-

import ctypes


class Strange:
    class ParameterInterval(ctypes.Structure):
        _fields_ = [("mina", ctypes.c_double),
                    ("maxa", ctypes.c_double),
                    ("minb", ctypes.c_double),
                    ("maxb", ctypes.c_double),
                    ("minc", ctypes.c_double),
                    ("maxc", ctypes.c_double),
                    ("mind", ctypes.c_double),
                    ("maxd", ctypes.c_double)]

    class Parameter(ctypes.Structure):
        _fields_ = [("a", ctypes.c_double),
                    ("b", ctypes.c_double),
                    ("c", ctypes.c_double),
                    ("d", ctypes.c_double)]

    def __init__(self):
        self.libstrange = ctypes.CDLL("./libstrange.so")

        test = self.libstrange.test
        test.restype = ctypes.c_double
        test.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]

        a = (ctypes.c_double * 5)()
        l = len(a)

        for i in range(l):
            a[i] = 1.2

        print(test(a, l))

        for i in a:
            print(i)

        parameters_test = self.libstrange.parameters_test

        p = Strange.Parameter(0, 1, 2, 3)

        print(parameters_test(p))


if __name__ == '__main__':
    s = Strange()
