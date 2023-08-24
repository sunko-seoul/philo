CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus
SRCS = src/main.c\
	  src/util/error.c\
	  src/util/ft_atoi.c\
	  src/util/malloc.c\
	  src/util/ft_itoa.c\
	  src/util/ft_strjoin.c\
	  src/util/error_util.c\
	  src/util/malloc_util.c\
	  src/all_free.c\
	  src/init.c\
	  src/moniter.c\
	  src/sem_print.c\
	  src/simulate.c\
	  src/simulate_util.c
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
