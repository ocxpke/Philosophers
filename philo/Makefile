NAME = philo

NAME_BONUS = philo_bonus

SRC = philosophers.c \
	philo_aux.c\
	ft_usleep.c\
	philo_life.c\
	manage_args.c\
	manage_time.c\
	monitor_aux.c\
	manage_monitor.c\
	philo_life_aux.c\
	manage_philosophers.c\

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g -O3

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
