# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstupar <fstupar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 04:32:29 by lraffin           #+#    #+#              #
#    Updated: 2022/04/27 12:40:16 by fstupar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= pipex

FLAGS	= -Wall -Wextra -Werror -fsanitize=address

HEADER	= pipex.h

SRCS 	= main.c\
		  ft_split.c\
		  utils.c
		  
OBJS	= $(SRCS:c=o)
			

CC		= gcc

RM		= rm -f

LIBFT 	= libft/libft.a

LIBFT_DIR = libft

all: $(NAME) 

/%.o: %.c
			$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L $(LIBFT_DIR) -lft

clean:
	rm -f $(OBJS)
	make -s clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make -s fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
