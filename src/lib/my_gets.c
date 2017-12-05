#include "lib.h"

int             my_atoi(const char *str)
{
        int     ret = 0;
        short   sign = 1;
        size_t  i = 0;

        while (str[i] == '-' || str[i] == '+') {
                if (str[i++] == '-') {
                        sign = -sign;
                }
        }
        while (str[i] >= '0' && str[i] <= '9') {
                ret = ret * 10 - '0' + str[i++];
        }
        return (ret * sign);
}

char                    *get_next_line(const int fd)
{
        static char     buf[READ_SIZE];
        static int      rd = 0;
        static int      s_rd = 0;
        char            *s = NULL;
        char            nc = 0;
        size_t          i = 0;

        if (!(s = malloc(sizeof(char) * (READ_SIZE + 1))))
                return (NULL);
        while (nc != '\n') {
                if (!rd && my_memset(buf, 0, READ_SIZE) &&
                (s_rd = (rd = read(fd, buf, READ_SIZE))) && s_rd <= 0)
                        return (NULL);
                if (((nc = buf[((rd--) - s_rd) * -1]) != '\n' &&
                !(s[i++] = nc)) || (!(i % READ_SIZE) && !(s[i] = 0) &&
                !(s = my_realloc(s, sizeof(char) * (i + READ_SIZE + 1)))))
                        return (NULL);
        }
        s[i] = 0;
        return (s);
}
