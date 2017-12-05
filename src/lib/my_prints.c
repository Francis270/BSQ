#include "lib.h"

int             my_putchar(const char c, const int fd)
{
        int     ret = 0;

        ret = write(fd, &c, 1);
        return (ret);
}

int             my_putstr(const char *str, const int fd)
{
        int     ret = 0;

        ret = write(fd, str, my_strnlen(str, 0));
        return (ret);
}

int		my_putnbrb(int nb, const char *base, const int fd)
{
        int     ret = 0;
        size_t  len = my_strnlen(base, 0);

        if (nb < 0 && (nb = -nb) > 0 && (ret += my_putchar('-', fd)) == -1)
                return (ret);
        if ((nb > ((int)len - 1) || nb < -((int)len - 1)) &&
        (ret += my_putnbrb((nb / len), base, fd)) == -1)
                return (ret);
        if ((nb % 10) >= 0) {
                if ((ret += my_putchar(base[nb % len], fd)) == -1)
                        return (ret);
        }
        else {
                if ((ret += my_putchar(base[nb % len] * (-1), fd)) == -1)
                        return (ret);
        }
        return (ret);
}

int             my_printf(const int fd, const char *fmt, ...)
{
        va_list ap;
        ssize_t i = -1;
        int     ret = 0;

        va_start(ap, fmt);
        while (fmt[++i]) {
                if (fmt[i] == '%' && fmt[i + 1]) {
                        if ((fmt[++i] == 'c' &&
                        (ret = my_putchar((char)va_arg(ap, int), fd)) == -1) ||
                        (fmt[i] == 's' &&
                        (ret = my_putstr(va_arg(ap, char *), fd)) == -1) ||
                        (fmt[i] == 'd' &&
                        (ret = my_putnbrb(va_arg(ap, int), D_BASE, fd)) == -1))
                                return (ret);
                }
                else if (fmt[i] != '%' && (ret = my_putchar(fmt[i], fd)) == -1)
                        return (ret);
        }
        va_end(ap);
        return (ret);
}
