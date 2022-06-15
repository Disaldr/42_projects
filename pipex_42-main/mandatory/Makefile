# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmumm <kmumm@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 05:50:46 by kmumm             #+#    #+#              #
#    Updated: 2022/06/13 22:58:39 by kmumm            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	../libft
LIBFT_LIB	=	libft.a

HEADER		=	pipex.h
SRC			=	pipex.c \
				parse_pipex.c

OBJ_DIR	=	obj
OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

INCLUDES	= 	-I .

${NAME}:	${OBJ}
			@$(CC) -o $(NAME) $(OBJ) $(FLAGS) ${LIBFT_DIR}/${LIBFT_LIB}
			@echo "\tCompiling\t" [ $(NAME) ] "\t\t" $(SUCCESS)
									
$(OBJ)		:	| $(OBJ_DIR)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o :	%.c $(HEADER) Makefile
					@${CC} $(FLAGS) $(INCLUDES) -o $@ -c $<

#COLORS
C_NO="\033[00m"
C_OK="\033[32m"
C_GOOD="\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)
			
all:	$(NAME)

clean:
		@${RM_DIR} ${OBJ_DIR}
		@echo "\tCleaning\t" [ $(NAME) ] "\t\t" $(OK)
		
fclean:	clean
		@${RM_FILE} $(NAME)
		@echo "\tDeleting\t" [ $(NAME) ] "\t\t" $(OK)
		
re:		fclean all

.PHONY: all clean fclean re

