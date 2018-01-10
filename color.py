class Color:
    def __init__(self):
        self.mode = None

    def set_solid_color(self, r, g, b):
        self.mode = 'solid'
        self.r = r
        self.g = g
        self.b = b

    def set_grad(self, r1, g1, b1, r2, g2, b2):
        self.mode = 'grad'

        self.r1 = r1
        self.g1 = g1
        self.b1 = b1

        self.r2 = r2
        self.g2 = g2
        self.b2 = b2

    def set_pal(self, path):
        self.mode = 'pal'
        self.path = path

        mode = 0

        self.data = []
        self.pal_len = 0

        raw = []

        with open(path) as f:
            for l in f.readlines():
                line = l.rstrip().lstrip()

                if line[0] == '#':
                    # print('found comment')
                    continue

                if line == 'P3' and mode == 0:
                    mode = 1
                    # print('found P3')
                elif mode == 1:
                    self.pal_len = int(line.split(' ')[0])
                    # print('found %d    .' % self.pal_len)
                    mode = 2
                elif line == '255' and mode == 2:
                    # print('found 255')
                    mode = 3
                elif mode == 3:
                    for token in line.split(' '):
                        raw.append(int(token))
                else:
                    print('panic at mode %d' % mode)
                    return

        for i in range(self.pal_len):
            self.data.append((raw[i * 3 + 0], raw[i * 3 + 1], raw[i * 3 + 2]))

    def __getitem__(self, key):
        if self.mode == 'solid':
            r = self.r
            g = self.g
            b = self.b
        elif self.mode == 'grad':
            r = self.r1 + key * (self.r2 - self.r1)
            g = self.g1 + key * (self.g2 - self.g1)
            b = self.b1 + key * (self.b2 - self.b1)
        elif self.mode == 'pal':
            index = -1
            try:
                index = int(key * self.pal_len)
                color = self.data[index]
                r = color[0]
                g = color[1]
                b = color[2]
            except Exception as e:
                print(e)
                # print(index, self.pal_len, len(self.data))

        return (r / 255.0, g / 255.0, b / 255.0)

    def info(self):
        print('color info:')

        if self.mode is None:
            print('colorManager was not initialized')
        elif self.mode == 'solid':
            print('using solid color (%3d, %3d, %3d)' % (self.r, self.g, self.b))
        elif self.mode == 'grad':
            print('using grad color from (%3d, %3d, %3d) to (%3d, %3d, %3d)' % (self.r1, self.g1, self.b1, self.r2, self.g2, self.b2))
        elif self.mode == 'pal':
            print('using palette %s' % self.path)
