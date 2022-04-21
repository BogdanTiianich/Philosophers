# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 18:30:43 by hbecki            #+#    #+#              #
#    Updated: 2022/04/21 19:44:48 by hbecki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			philo

NAME_BONUS =	philo_bonus
HEAD =			./mandatory/philosophers.h

# GNL_HEAD = get_next_line/get_next_line.h

# LIBDIR = 		./libft/

# LIBFT = 		libft.a

# CHECKERDIR = 	./checker/

HEAD_BONUS =	./bonus/philosophers_bonus.h

SRC =  mandatory/philosophers.c\
		# mandatory/pipex_utils1.c\
		# mandatory/pipex_utils2.c\
		# mandatory/pipex_utils3.c\
		# mandatory/pipex_utils4.c\
		# mandatory/pipex_utils5.c

SRC_BONUS = bonus/philosophers_bonus.c\
# 		bonus/pipex_utils1_bonus.c\
# 		bonus/pipex_utils2_bonus.c\
# 		bonus/pipex_utils3_bonus.c\
# 		bonus/pipex_utils4_bonus.c\
# 		bonus/pipex_utils5_bonus.c

# SRC_GNL = get_next_line/get_next_line.c\
# 			get_next_line/get_next_line_utils.c

OBJ =			$(SRC:%.c=%.o)

OBJ_BONUS =		$(SRC_BONUS:%.c=%.o)

OBJ_GNL = $(SRC_GNL:%.c=%.o)

D =				$(SRC:%.c=%.d)

D_BONUS =		$(SRC_BONUS:%.c=%.d)

CFLAGS = 		#-Wall -Werror -Wextra

THR = 			-g -pthread
CC = 			gcc 

RM = 			rm -f

all : 			$(NAME)

$(NAME) : 		$(OBJ) #$(OBJ_GNL)
				$(CC) $(CFLAGS) $(OBJ) -o $@

libmake :
				@make -C $(LIBDIR)
checker_make :
				@make -C $(CHECKERDIR)

OBJ_GNL :		$(SRC_GNL) $(GNL_HEAD)
				$(CC) $(CFLAGS) -c $< -o $@	
	
%.o : 			%.c $(HEAD)
				$(CC) $(CFLAGS) $(THR) -I $(HEAD) -c $< -o $@

include 		$(wildcard $(D) $(D_BONUS))

bonus:
				@make OBJ="$(OBJ_BONUS)" HEAD="$(HEAD_BONUS)" NAME="$(NAME_BONUS)" all

clean:
				@make clean -C $(LIBDIR)
				@$(RM) $(OBJ) $(D) $(D_BONUS) $(OBJ_BONUS) $(OBJ_GNL)

fclean: 		clean
				@$(RM) $(NAME) $(LIBFT)

re: 			fclean all

.PHONY: 		all clean fclean re bonus