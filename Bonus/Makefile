NAME = philo_bonus
CC = gcc
CFLAGS = -Wextra -Werror -Wall #-fsanitize=thread -g -O1 
H_PATH = -I.
PTHREAD_FLAG = -pthread
DODIR = dofile
SRCS = main.c \
	   check_args.c \
	   data_init.c \
	   simulation.c \
	   philo_routine.c \
	   safe_modules.c \
	   utils.c

OBJS = $(patsubst %.c,$(DODIR)/%.o,$(SRCS))

#Default target
all: $(NAME)

#Rule to link
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD_FLAG) $(OBJS) -o $(NAME)

#Rule to compile and generate d files
$(OBJS):$(DODIR)/%.o:%.c | $(DODIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(H_PATH) $(PTHREAD_FLAG) -c $< -o $@

$(DODIR):
	mkdir -p $@

clean:
	rm -f $(OBJS) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re