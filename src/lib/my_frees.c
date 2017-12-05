#include "lib.h"

bool            my_free(void *ptr)
{
        if (ptr)
                free(ptr);
        return (true);
}
