NAME = philosophers

SOURCES = ./get_set_forks.c\
./philo_eat.c\
./get_set_times_and_eat.c\
./philo_routine.c\
./check_input.c\
./init.c\
./philosophers.c\
./print_state.c\
./get_set_flags.c\
./thread_controller.c\
./join_threads.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

OBJECTS = $(SOURCES:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
		$(RM) $(OBJECTS)
fclean:	clean
		$(RM) $(NAME)
re:		fclean all

.PHONY: all, clean, fclean, re