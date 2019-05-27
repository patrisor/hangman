# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrisor <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/11 18:00:18 by patrisor          #+#    #+#              #
#    Updated: 2019/05/11 18:19:15 by patrisor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_hangman

SRCS = ft_hangman.c

OBJ = *.o

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) :
	@make -C libft/
	@gcc $(FLAGS) -I libft/includes/ -c $(SRCS)
	@gcc $(OBJ) -L libft/ -lft -o $(NAME)

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
