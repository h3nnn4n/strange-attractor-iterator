#!/usr/bin/python3.5
# -*- coding: utf-8 -*-

import ctypes
import math


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

    class ImgOpt(ctypes.Structure):
        _fields_ = [("frames", ctypes.c_int),
                    ("skipIters", ctypes.c_int),
                    ("iters", ctypes.c_int),
                    ("screenx", ctypes.c_int),
                    ("screeny", ctypes.c_int),
                    ("sens", ctypes.c_double)]

    class Bounds(ctypes.Structure):
        _fields_ = [("minx", ctypes.c_double),
                    ("maxx", ctypes.c_double),
                    ("miny", ctypes.c_double),
                    ("maxy", ctypes.c_double)]

    class Color(ctypes.Structure):
        _fields_ = [("r", ctypes.c_double),
                    ("g", ctypes.c_double),
                    ("b", ctypes.c_double)]

    def __init__(self):
        self.libstrange = ctypes.CDLL("./libstrange.so")

        # foo = self.libstrange.foo
        foo = self.libstrange.cliff
        foo.restype = ctypes.c_double
        # foo.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]

        parameters = Strange.Parameter(-1.4, 1.6, 1.0, 0.7)
        parameter_interval = Strange.ParameterInterval()
        image_config = Strange.ImgOpt(5000, 500, 5000000, 800, 600, 0.01)

        color = Strange.Color(1.0, 0.0, 0.5)
        bitmap = (Strange.Color * image_config.screenx * image_config.screeny)()

        bounds = Strange.Bounds(9999, -9999, 9999, -9999)
        pbounds = ctypes.pointer(bounds)

        self.image_config = image_config
        self.bitmap = bitmap
        self.parameters = parameters
        self.parameter_interval = parameter_interval
        self.color = color
        self.foo = foo
        self.bounds = bounds
        self.pbounds = pbounds

    def test(self):
        self.foo(self.parameters, self.image_config, self.bitmap, self.pbounds, 0, self.color)
        self.foo(self.parameters, self.image_config, self.bitmap, self.pbounds, 1, self.color)

    def save(self):
        with open('uhull.ppm', 'wt') as f:
            f.write('P3\n')
            f.write('%d %d\n' % (self.image_config.screenx, self.image_config.screeny))
            f.write('%d\n' % (255))

            for j in range(self.image_config.screeny):
                for i in range(self.image_config.screenx):
                    f.write("%d %d %d " % (math.ceil(self.bitmap[j][i].r), math.ceil(self.bitmap[j][i].g), math.ceil(self.bitmap[j][i].b)))
                f.write('\n')


if __name__ == '__main__':
    s = Strange()
    s.test()
    s.save()
