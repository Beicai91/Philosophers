NAME = philo
CC = gcc 
CFLAGS = -Wextra -Wall -Werror -g3
H_PATH = -I.
PTHREAD_FLAG = -pthread
DODIR = dofile
SRCS = check_args.c \
	   data_init.c \
	   main.c \
	   monitor_routine.c \
	   philo_routine.c \
	   safe_modules.c \
	   simulation.c \
	   utils.c

#DEFINE object files
OBJS = $(patsubst %.c,$(DODIR)/%.o,$(SRCS))

#DEFINE dependancy files
#DEP = $(patsubst %.o,%.d,$(OBJS))

#Default target
all: $(NAME)

#include dependancy files: SHOULD BE PLACED AFTER DEFAULT TARGET
#-include $(DEP)

#Rule to link the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD_FLAG) $(OBJS) -o $(NAME)

#Rule to compile source file into object files, dependancy files are generated as well during the compilation phase
#| $(DODIR): Order-only prerequisite, ensures that the $(DODIR) directory exists before attempting to create object files.
# $(dir $@): Extracts the directory part of the target file path. For example, if $@ is dofile/check_args.o, $(dir $@) would be dofile/.
# if we are sure that all o files will be in DODIR without any subdirectories, we can also use `@mkdir -p $(DODIR)`
$(OBJS): $(DODIR)/%.o: %.c | $(DODIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLGAS) $(H_PATH) $(PTHREAD_FLAG) -c $< -o $@ 

#Rule to create the DODIR. -p makes sure that if it exists already, nothing will be done
$(DODIR):
	mkdir -p $@

#Rule to clean object files and other temporary files
clean:
	rm -f $(OBJS) $(DEP)

#Rule to fully clean, including the executable
fclean: clean
	rm -f $(NAME)

#Rule to remake the executable
re: fclean all

.PHONY: all clean fclean re
