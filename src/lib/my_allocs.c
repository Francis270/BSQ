#include "lib.h"

void            *my_realloc(void *ptr, const size_t size)
{
        void    *new_mem = NULL;

        if (!size) {
                my_free(ptr);
                return (NULL);
        }
        new_mem = malloc(size);
        if (!new_mem) {
                return (NULL);
        }
        if (!ptr) {
                return (new_mem);
        }
        my_memcpy(new_mem, ptr, size);
        my_free(ptr);
        return (new_mem);
}
