#ifndef LIB_H_
# define LIB_H_

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>

# define READ_SIZE        (0x200)
# define D_BASE           ("0123456789")

size_t                  my_strnlen(const char *, const size_t);
void                    *my_memset(void *, const int, const size_t);
void                    *my_memcpy(void *, const void *, const size_t);

bool                    my_free(void *);

int                     my_atoi(const char *);
char                    *get_next_line(const int);

void                    *my_realloc(void *, const size_t);

int                     my_printf(const int, const char *, ...);
int		        my_putnbrb(int, const char *, const int);
int                     my_putstr(const char *, const int);
int                     my_putchar(const char, const int);


#endif /* !LIB_H_ */
