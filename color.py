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
            pass

        return (r, g, b)
