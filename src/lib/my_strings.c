#include "lib.h"

size_t          my_strnlen(const char *s, const size_t maxlen)
{
        size_t  i = 0;
        size_t  max = maxlen;

        if (s && max == 0) {
                while (s[i]) {
                        i++;
                }
        }
        else if (s && max) {
                while (s[i] && max-- > 0) {
                        i++;
                }
        }
        return (i);
}

void                    *my_memcpy(void *dest, const void *src, const size_t n)
{
        char            *dp = dest;
        const char      *sp = src;
        size_t          i = n;

        if (i) {
                i++;
                while (--i) {
                        *dp++ = *sp++;
                }
        }
        return (dest);
}

void            *my_memset(void *s, const int c, const size_t n)
{
        char    *d = (char *)s;
        size_t  i = n;

        if (i) {
                i++;
                while (--i) {
                        *d++ = (unsigned char)c;
                }
        }
        return (s);
}
