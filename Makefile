NAME		= bsq

SRCS		= main.c \
		  lib/my_allocs.c \
		  lib/my_frees.c \
		  lib/my_prints.c \
		  lib/my_strings.c \
		  lib/my_gets.c

OBJS		= $(addprefix src/, $(SRCS:.c=.o))

CC		= gcc

RM		= rm -f

CFLAGS	= 	-Iinclude/ \
		-W -Wall -Wextra \
		-Wno-unused-parameter \
		-ansi -pedantic \
		-std=gnu99 \

LDFLAGS		= $(LIBS)

ifeq		($(DEBUG),yes)
		CC += -g3
endif

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LDFLAGS)

all:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
