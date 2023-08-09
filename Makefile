# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edupless <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 18:26:39 by edupless          #+#    #+#              #
#    Updated: 2023/08/08 18:27:38 by edupless         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror  
LIBMLX	= ./lib/MLX42
LIBFT	= lib/libft
LIBF	= libft.a
HEADERS	= -I ./include -I $(LIBMLX)/include   
SRCS	= $(shell find ./src -iname "*.c")
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
