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
        # self.libcolor = ctypes.CDLL("./libcolor.so")
        self.libmagic = ctypes.CDLL("./libmagic.so")

        cliff = self.libmagic.cliff
        # cliff.restype = ctypes.c_double
        # cliff.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.c_int]

        parameters = Strange.Parameter(-1.4, 1.6, 1.0, 0.7)
        parameter_interval = Strange.ParameterInterval()
        image_config = Strange.ImgOpt(1000, 500, 50000, 800, 600, 0.001)

        color = Strange.Color(1.0, 0.0, 0.5)
        bitmap = (Strange.Color * image_config.screenx * image_config.screeny)()

        bounds = Strange.Bounds(9999, -9999, 9999, -9999)
        pbounds = ctypes.pointer(bounds)

        self.image_config = image_config
        self.bitmap = bitmap
        self.parameters = parameters
        self.parameter_interval = parameter_interval
        self.color = color
        self.cliff = cliff
        self.bounds = bounds
        self.pbounds = pbounds

    def test(self):
        self.cliff(self.parameters, self.image_config, self.bitmap, self.pbounds, 0, self.color)
        self.cliff(self.parameters, self.image_config, self.bitmap, self.pbounds, 1, self.color)

    def eval_bounds(self):
        iters = self.image_config.iters
        self.image_config.iters = iters // 10

        print('Evaluating bounds')

        for i in range(0, self.image_config.frames, 10):
            self.update_parameters(i)
            self.cliff(self.parameters, self.image_config, self.bitmap, self.pbounds, 0, self.color)

        self.image_config.iters = iters

        bounds = self.bounds
        print("Bounds are: (%6.3f, %6.3f) and (%6.3f, %6.3f)" % (bounds.minx, bounds.maxx, bounds.miny, bounds.maxy))

    def run(self):
        print('Running')

        for i in range(self.image_config.frames):
            if (i + 1) % (self.image_config.frames // 10) == 0:
                print("%4.1f%%" % (((i + 1) / self.image_config.frames) * 100.0))
            self.update_parameters(i)
            self.cliff(self.parameters, self.image_config, self.bitmap, self.pbounds, 1, self.color)

    def update_parameters(self, i):
        p = i / self.image_config.frames

        self.parameters.a = self.parameter_interval.mina + p * (self.parameter_interval.maxa - self.parameter_interval.mina)
        self.parameters.b = self.parameter_interval.minb + p * (self.parameter_interval.maxb - self.parameter_interval.minb)
        self.parameters.c = self.parameter_interval.minc + p * (self.parameter_interval.maxc - self.parameter_interval.minc)
        self.parameters.d = self.parameter_interval.mind + p * (self.parameter_interval.maxd - self.parameter_interval.mind)

    def save(self):
        def write_png(buf, width, height):
            import zlib
            import struct

            width_byte_4 = width * 4
            raw_data = b''.join(b'\x00' + buf[span:span + width_byte_4]
                                for span in range((height - 1) * width_byte_4, -1, - width_byte_4))

            def png_pack(png_tag, data):
                chunk_head = png_tag + data
                return (struct.pack("!I", len(data)) +
                        chunk_head +
                        struct.pack("!I", 0xFFFFFFFF & zlib.crc32(chunk_head)))

            return b''.join([
                b'\x89PNG\r\n\x1a\n',
                png_pack(b'IHDR', struct.pack("!2I5B", width, height, 8, 6, 0, 0, 0)),
                png_pack(b'IDAT', zlib.compress(raw_data, 9)),
                png_pack(b'IEND', b'')])

        buf = bytearray(self.image_config.screenx * self.image_config.screeny * 4)

        for j in range(self.image_config.screeny):
            for i in range(self.image_config.screenx):
                p = (self.bitmap[j][i].r, self.bitmap[j][i].g, self.bitmap[j][i].b, 0xff)

                buf[(j * self.image_config.screenx + i) * 4 + 0] = math.floor(((1.0 - math.exp(-self.image_config.sens * p[0])) * 255.0))
                buf[(j * self.image_config.screenx + i) * 4 + 1] = math.floor(((1.0 - math.exp(-self.image_config.sens * p[1])) * 255.0))
                buf[(j * self.image_config.screenx + i) * 4 + 2] = math.floor(((1.0 - math.exp(-self.image_config.sens * p[2])) * 255.0))
                buf[(j * self.image_config.screenx + i) * 4 + 3] = p[3] % 256

        data = write_png(buf, self.image_config.screenx, self.image_config.screeny)
        with open("my_image.png", 'wb') as fd:
            fd.write(data)


if __name__ == '__main__':
    s = Strange()

    s.parameter_interval.mina = s.parameters.a
    s.parameter_interval.maxa = s.parameters.a

    s.parameter_interval.minb = s.parameters.b
    s.parameter_interval.maxb = s.parameters.b

    s.parameter_interval.minc = s.parameters.c
    s.parameter_interval.maxc = s.parameters.c

    s.parameter_interval.mind = s.parameters.d
    s.parameter_interval.maxd = s.parameters.d

    s.parameter_interval.maxd = s.parameters.d + 0.2

    s.eval_bounds()

    s.run()

    s.save()
