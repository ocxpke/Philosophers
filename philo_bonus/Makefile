NAME = philo_bonus

SRC = philosopher_bonus.c \
	ft_itoa.c\
	philo_aux.c\
	ft_usleep.c\
	philo_life.c\
	manage_args.c\
	manage_time.c\
	manage_philos.c\
	manage_monitor.c\
	philo_life_aux.c

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

re: fclean clean re all
