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
        self.cliff = cliff
        self.bounds = bounds
        self.pbounds = pbounds

    def test(self):
        self.cliff(self.parameters, self.image_config, self.bitmap, self.pbounds, 0, self.color)
        self.cliff(self.parameters, self.image_config, self.bitmap, self.pbounds, 1, self.color)

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
                p = (math.ceil(self.bitmap[j][i].r), math.ceil(self.bitmap[j][i].g), math.ceil(self.bitmap[j][i].b), 0xff)

                buf[(j * self.image_config.screenx + i) * 4 + 0] = p[0] % 256
                buf[(j * self.image_config.screenx + i) * 4 + 1] = p[1] % 256
                buf[(j * self.image_config.screenx + i) * 4 + 2] = p[2] % 256
                buf[(j * self.image_config.screenx + i) * 4 + 3] = p[3] % 256

        data = write_png(buf, self.image_config.screenx, self.image_config.screeny)
        with open("my_image.png", 'wb') as fd:
            fd.write(data)


if __name__ == '__main__':
    s = Strange()
    s.test()
    s.save()
