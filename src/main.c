#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include "lib.h"

static void     display_map(const t_bsq *data)
{
        size_t  c = 0;
        size_t  w = 0;
        size_t  h = 1;

        while (++c < ((data->x * data->y) + 1)) {
                if (++w > data->max_pos && w <= (data->max + data->max_pos) &&
                h <= data->max)
                        my_printf(1, "x");
                else
                        my_printf(1, "%c", (!data->map[c - 1]) ? 'o' : '.');
                if (!(c % (data->x)) && c) {
                        my_printf(1, "\n");
                        h++;
                        w = 0;
                }
        }
}

static size_t   get_min(const t_bsq *data, const ssize_t x)
{
        size_t  a = data->map[x + data->x];
        size_t  b = data->map[x + data->x + 1];
        size_t  c = data->map[x + 1];
        size_t  is_min = 0;

        if (a <= b && a <= c)
                is_min = a;
        else if (b <= a && b <= c)
                is_min = b;
        else if (c <= a && c <= b)
                is_min = c;
        return (is_min + 1);
}

static bool     path_finding(t_bsq *data, size_t i, ssize_t x)
{
        while (++i != data->y) {
                data->map[(i * data->x) - 1] =
                (data->map[(i * data->x) - 1] == '.') ? 1 : 0;
        }
        i = (data->x * data->y) - data->x - 1;
        while (++i != (data->x * data->y)) {
                data->map[i] = (data->map[i] == '.') ? 1 : 0;
        }
        while (--x >= 0) {
                if (data->map[x] == '.') {
                        data->map[x] = get_min(data, x);
                        if (data->map[x] >= data->max) {
                                data->max = data->map[x];
                                data->max_pos = x;
                        }
                }
                else if (data->map[x] == 'o')
                        data->map[x] = 0;
        }
        return (true);
}

static bool         stock_map(t_bsq *data, const int fd, const char *file)
{
        struct stat st;
        ssize_t     i = -1;
        ssize_t     l = -1;
        size_t      h = 0;
        char        *tmp = NULL;

        if (stat(file, &st) == -1 ||
        !(data->map = malloc(sizeof(size_t) * (st.st_size + 1))) ||
        !(tmp = get_next_line(fd)) || !(h = my_atoi(tmp)) || !my_free(tmp))
                return (false);
        while ((tmp = get_next_line(fd))) {
                i = -1;
                while (tmp[++i])
                        data->map[++l] = (tmp[i] == 'o') ? 111 : 46;
                my_free(tmp);
        }
        data->x = i;
        data->y = (l + 1) / i;
        return (h != data->y) ? false : true;
}

int		main(int argc, char **argv)
{
        t_bsq   data;
        int     fd = 0;

        if (argc != 2 || !argv[1])
                return (84);
        if ((fd = open(argv[1], O_RDONLY)) == -1)
                return (84);
        my_memset(&data, 0, sizeof(data));
        if (!stock_map(&data, fd, argv[1]))
                return (84);
        if (close(fd) == -1)
                return (84);
        if (!path_finding(&data, 0, (data.x * data.y) - data.x - 1))
                return (84);
        display_map(&data);
        my_free(data.map);
        return (0);
}
