NAME = philo

NAME_BONUS = philo_bonus

SRC = philosophers.c \
	ft_itoa.c\
	philo_life.c\
	manage_args.c\
	manage_time.c\
	manage_monitor.c\
	manage_philosophers.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

all:$(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -o $@ -c $<
