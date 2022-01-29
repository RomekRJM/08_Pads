from math import sin, cos, radians

MATH_S = '../math.s'


def compute_function(fun, v):
    return min(round(8 * fun(radians(v)) + 8), 255)


def build_struct(size):
    values = ['    '] * (size * 2)
    v = 0

    for x in range(size):
        values[x] += '.byte ' + str(compute_function(sin, v))
        v = v + 1.40625 * 256 / size

    for x in range(size, 2*size):
        values[x] += '.byte ' + str(compute_function(cos, v))
        v = v + 1.40625 * 256 / size

    return "\n".join(values)


def write_to_file(content, write_option='a', path=MATH_S):
    with open(path, write_option) as f:
        f.write(content)


if __name__ == '__main__':
    write_to_file('.segment	"RODATA"\n', 'w')
    write_to_file('.export		_virusPath\n')
    write_to_file('_virusPath:\n\n')
    write_to_file(build_struct(256))
    write_to_file('\n')
