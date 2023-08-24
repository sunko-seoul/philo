CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = src/main.c\
	   src/print.c\
	   src/simulate.c\
	   src/moniter.c\
	   src/simulate_util.c\
	   src/util/malloc.c\
	   src/util/get_idx.c\
	   src/util/atoi.c\
	   src/util/error.c\
	   src/util/time.c
OBJS = $(SRCS:.c=.o)
HEADER = include/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -I $(HEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
