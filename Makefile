# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 18:30:43 by hbecki            #+#    #+#              #
#    Updated: 2022/06/02 15:09:37 by hbecki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			philo

NAME_BONUS =	philo_bonus

HEAD =			./mandatory/philosophers.h

HEAD_BONUS =	./bonus/philosophers_bonus.h

SRC =  mandatory/philosophers.c\
	mandatory/func_args_handlers.c\
	mandatory/func_time.c\
	mandatory/init_funcs.c\
	mandatory/memory_func.c\
	mandatory/philos_routine_one.c\
	mandatory/philos_routine_two.c

SRC_BONUS = bonus/philosophers_bonus.c\
		bonus/func_args_handlers_bonus.c\
		bonus/func_time_bonus.c\
		bonus/init_funcs_bonus.c\
		bonus/memory_func_bonus.c\
		bonus/philos_routine_one_bonus.c\
		bonus/monitoring_bonus.c\
		bonus/philos_routine_two_bonus.c


OBJ =			$(SRC:%.c=%.o)

OBJ_BONUS =		$(SRC_BONUS:%.c=%.o)

OBJ_GNL = $(SRC_GNL:%.c=%.o)

D =				$(SRC:%.c=%.d)

D_BONUS =		$(SRC_BONUS:%.c=%.d)

CFLAGS = 		-Wall -Werror -Wextra

THR = 			-g -pthread

CC = 			gcc 

RM = 			rm -f

all : 			$(NAME)

$(NAME) : 		$(OBJ) 
				$(CC) $(CFLAGS) $(OBJ) -o $@
	
%.o : 			%.c $(HEAD)
				$(CC) $(CFLAGS) $(THR) -I $(HEAD) -c $< -o $@

include 		$(wildcard $(D) $(D_BONUS))

bonus:
				@make OBJ="$(OBJ_BONUS)" HEAD="$(HEAD_BONUS)" NAME="$(NAME_BONUS)" all

clean:

				@$(RM) $(OBJ) $(D) $(D_BONUS) $(OBJ_BONUS)

fclean: 		clean
				@$(RM) $(NAME) $(NAME_BONUS)

re: 			fclean all

.PHONY: 		all clean fclean re bonus