
NAME	= philo
CFLAGS	= -Wall -Wextra -Werror  
HEADERS	= -I ./include    
SRCS	= $(shell find ./srcs -iname "*.c")
OBJS_DIR= OBJS 
OBJS	= ${SRCS:.c=.o}

all:  $(NAME)


%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(LIBF) $(HEADERS) -o $(NAME)

clean:	
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
