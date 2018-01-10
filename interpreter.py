#!/usr/bin/python3.5
# -*- coding: utf-8 -*-

import tempfile
import color
import strange
import random


def pinfo(p):
    print('parameters info:')
    if p.mina == p.maxa:
        print('a = %7.3f' % (p.mina))
    else:
        print('a = [%7.3f, %7.3f]' % (p.mina, p.maxa))

    if p.minb == p.maxb:
        print('b = %7.3f' % (p.minb))
    else:
        print('b = [%7.3f, %7.3f]' % (p.minb, p.maxb))

    if p.minc == p.maxc:
        print('c = %7.3f' % (p.minc))
    else:
        print('c = [%7.3f, %7.3f]' % (p.minc, p.maxc))

    if p.mind == p.maxd:
        print('d = %7.3f' % (p.mind))
    else:
        print('d = [%7.3f, %7.3f]' % (p.mind, p.maxd))


if __name__ == '__main__':

    colors = {}
    parameters = {}
    attractor = {}

    active_color = None
    active_parameter = None
    active_attractor = None

    last_name = None

    while True:
        line = input('> ')
        tokens = line.split(' ')
        print(tokens)

        try:
            if tokens[0] == 'quit' or tokens[0] == 'exit':
                break

            elif tokens[0] == 'active':
                print('active attractor is %s' % active_attractor)
                print('active parameter is %s' % active_parameter)
                print('active color is %s' % active_color)

            elif tokens[0] == 'print':
                if tokens[1] == 'color':
                    colors[active_color].info()
                elif tokens[1] == 'parameter':
                    pinfo(parameters[active_parameter])
                elif tokens[1] == 'attractor':
                    attractor[active_attractor].info()

            elif tokens[0] == 'new':
                if len(tokens) == 1:
                    cname = 'color_' + next(tempfile._get_candidate_names())
                    pname = 'param_' + next(tempfile._get_candidate_names())
                    sname = 'attractor_' + next(tempfile._get_candidate_names())

                    colors[cname] = color.Color()
                    parameters[pname] = strange.Strange.ParameterInterval()
                    attractor[sname] = strange.Strange()
                    attractor[sname].set_color(colors[cname])
                    attractor[sname].parameter_interval = parameters[pname]

                    if active_attractor is None:
                        active_attractor = sname
                        active_parameter = pname
                        active_color = cname
                        print('active attractor is now %s' % active_attractor)
                        print('active color is now %s' % active_color)
                        print('active parameter is now %s' % active_parameter)

                elif tokens[1] == 'random':
                    cname = 'color_' + next(tempfile._get_candidate_names())
                    pname = 'param_' + next(tempfile._get_candidate_names())
                    sname = 'attractor_' + next(tempfile._get_candidate_names())

                    colors[cname] = color.Color()
                    parameters[pname] = strange.Strange.ParameterInterval()
                    attractor[sname] = strange.Strange()

                    parameters[pname].mina = random.random() * 4.0 - 2.0
                    parameters[pname].maxa = random.random() * 4.0 - 2.0

                    parameters[pname].minb = random.random() * 4.0 - 2.0
                    parameters[pname].maxb = random.random() * 4.0 - 2.0

                    parameters[pname].minc = random.random() * 4.0 - 2.0
                    parameters[pname].maxc = random.random() * 4.0 - 2.0

                    parameters[pname].mind = random.random() * 4.0 - 2.0
                    parameters[pname].maxd = random.random() * 4.0 - 2.0

                    attractor[sname].set_color(colors[cname])
                    attractor[sname].parameter_interval = parameters[pname]
                    r1 = random.randint(0, 255)
                    g1 = random.randint(0, 255)
                    b1 = random.randint(0, 255)
                    r2 = random.randint(0, 255)
                    g2 = random.randint(0, 255)
                    b2 = random.randint(0, 255)
                    colors[cname].set_grad(r1, g1, b1, r2, b2, g2)

                    if active_attractor is None:
                        active_attractor = sname
                        active_parameter = pname
                        active_color = cname
                        print('active attractor is now %s' % active_attractor)
                        print('active color is now %s' % active_color)
                        print('active parameter is now %s' % active_parameter)

                elif tokens[1] == 'color':
                    if len(tokens) == 2:
                        name = 'color_' + next(tempfile._get_candidate_names())
                    else:
                        name = tokens[2]

                    colors[name] = color.Color()
                    print('created color as %s' % name)
                    if active_attractor is not None and active_color is None:
                        active_color = name
                        print('active color is now %s' % active_color)
                        attractor[active_attractor].set_color(colors[name])

                elif tokens[1] == 'parameter':
                    if len(tokens) == 2:
                        name = 'param_' + next(tempfile._get_candidate_names())
                    else:
                        name = tokens[2]

                    parameters[name] = strange.Strange.ParameterInterval()
                    print('created parameter as %s' % name)
                    if active_attractor is not None and active_parameter is None:
                        active_parameter = name
                        print('active parameter is now %s' % active_parameter)
                        attractor[active_attractor].parameter_interval = parameters[name]

                elif tokens[1] == 'attractor':
                    if len(tokens) == 2:
                        name = 'attractor_' + next(tempfile._get_candidate_names())
                    else:
                        name = tokens[2]

                    attractor[name] = strange.Strange()
                    print('created attractor as %s' % name)
                    if active_attractor is None:
                        active_attractor = name
                        print('active attractor is now %s' % active_attractor)

            elif tokens[0] == 'set':
                if tokens[1] == 'active':
                    if tokens[2] == 'color':
                        if active_attractor is None:
                            print('set active_parameter first')
                        else:
                            if len(tokens) == 3:
                                name = 'color_' + next(tempfile._get_candidate_names())
                                colors[name] = color.Color()
                                print('color not specified, created color as %s' % name)
                            else:
                                name = tokens[3]
                                if name not in colors.keys():
                                    print('color not found, creating')
                                    colors[name] = color.Color()
                                    print('created color as %s' % name)

                            active_color = name
                            print('active colors is now %s' % active_color)
                    elif tokens[2] == 'parameter':
                        pass
                    elif tokens[2] == 'attractor':
                        pass

                elif tokens[1] == 'color':
                    if active_color is None:
                        print('active color not set')
                    elif tokens[2] == 'solid':
                        if tokens[3] == 'random':
                            r = random.randint(0, 255)
                            g = random.randint(0, 255)
                            b = random.randint(0, 255)
                        else:
                            r = int(tokens[3])
                            g = int(tokens[4])
                            b = int(tokens[5])
                        colors[active_color].set_solid_color(r, g, b)
                    elif tokens[2] == 'grad':
                        if tokens[3] == 'random':
                            r1 = random.randint(0, 255)
                            g1 = random.randint(0, 255)
                            b1 = random.randint(0, 255)
                            r2 = random.randint(0, 255)
                            g2 = random.randint(0, 255)
                            b2 = random.randint(0, 255)
                        else:
                            r1 = int(tokens[3])
                            g1 = int(tokens[4])
                            b1 = int(tokens[5])
                            r2 = int(tokens[6])
                            g2 = int(tokens[7])
                            b2 = int(tokens[8])
                        colors[active_color].set_grad(r1, g1, b1, r2, b2, g2)
                    elif tokens[2] == 'pal':
                        path = tokens[3]
                        colors[active_color].set_pal(path)

                elif tokens[1] == 'parameter':
                    if tokens[2] == 'random':
                        if len(tokens) == 3:
                            parameters[active_parameter].mina = random.random() * 4.0 - 2.0
                            parameters[active_parameter].maxa = random.random() * 4.0 - 2.0

                            parameters[active_parameter].minb = random.random() * 4.0 - 2.0
                            parameters[active_parameter].maxb = random.random() * 4.0 - 2.0

                            parameters[active_parameter].minc = random.random() * 4.0 - 2.0
                            parameters[active_parameter].maxc = random.random() * 4.0 - 2.0

                            parameters[active_parameter].mind = random.random() * 4.0 - 2.0
                            parameters[active_parameter].maxd = random.random() * 4.0 - 2.0
                        attractor[active_attractor].parameter_interval = parameters[active_parameter]
            elif tokens[0] == 'eval_bounds':
                attractor[active_attractor].eval_bounds()
            elif tokens[0] == 'render':
                attractor[active_attractor].run()
            elif tokens[0] == 'run':
                attractor[active_attractor].eval_bounds()
                attractor[active_attractor].run()
            elif tokens[0] == 'save':
                if len(tokens) == 1:
                    attractor[active_attractor].save()
                    last_name = 'out.png'
                else:
                    attractor[active_attractor].save(tokens[1])
                    last_name = tokens[1] + '.png'
            elif tokens[0] == 'show':
                import subprocess
                subprocess.call(['feh', last_name])

        except Exception as e:
            print(e)
