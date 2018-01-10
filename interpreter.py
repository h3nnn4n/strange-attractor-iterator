#!/usr/bin/python3.5
# -*- coding: utf-8 -*-

import tempfile
import color
import strange


if __name__ == '__main__':

    colors = {}
    parameters = {}
    attractor = {}

    active_color = None
    active_parameter = None
    active_attractor = None

    while True:
        line = input('> ')
        tokens = line.split(' ')
        print(tokens)

        try:
            if tokens[0] == 'quit' or tokens[0] == 'exit':
                break
            elif tokens[0] == 'new':
                if len(tokens) == 1:
                    cname = 'color_' + next(tempfile._get_candidate_names())
                    pname = 'param_' + next(tempfile._get_candidate_names())
                    sname = 'attractor_' + next(tempfile._get_candidate_names())

                    colors[cname] = color.Color()
                    parameters[pname] = strange.Strange.ParameterInterval()
                    attractor[sname] = strange.Strange()

                    attractor[sname].set_color(colors[cname])

                    if active_attractor is None:
                        active_attractor = sname
                        print('active attractor is now %s' % active_attractor)

                elif tokens[1] == 'color':
                    if len(tokens) == 2:
                        name = 'color_' + next(tempfile._get_candidate_names())
                    else:
                        name = tokens[2]

                    colors[name] = color.Color()
                    print('created color as %s' % name)

                elif tokens[1] == 'parameter':
                    if len(tokens) == 2:
                        name = 'param_' + next(tempfile._get_candidate_names())
                    else:
                        name = tokens[2]

                    parameters[name] = strange.Strange.ParameterInterval()
                    print('created parameter as %s' % name)

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
                        elif len(tokens) == 3:
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
        except Exception as e:
            print(e)
