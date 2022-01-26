from math import sin, cos, radians

MATH_S = '../math.s'


def compute_function(fun, v):
    return min(round(8 * fun(radians(v)) + 8), 255)


def build_struct():
    values = ['    '] * 1024
    v = 0

    for x in range(256):
        values[x*4] += '.byte ' + str(compute_function(sin, v))
        values[x*4+1] += '.byte 00'
        values[x*4+2] += '.byte ' + str(compute_function(cos, v))
        values[x*4+3] += '.byte 00'
        v = v + 1.40625

    return "\n".join(values)


def write_to_file(content, write_option='a', path=MATH_S):
    with open(path, write_option) as f:
        f.write(content)


if __name__ == '__main__':
    write_to_file('.segment	"RODATA"\n', 'w')
    write_to_file('.export		_virusPath\n')
    write_to_file('_virusPath:\n\n')
    write_to_file(build_struct())
    write_to_file('\n')
