#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 17:16:53 by vdoroshy          #+#    #+#              #
#    Updated: 2017/04/20 17:16:56 by vdoroshy         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
HEADER = lem_in.h

OBJECTS = lem_in.o \
			aug_lib.o \
			validate_ants.o \

.PHONY : clean all fclean re

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft/$(LIBFT)

$(LIBFT) :
	make -C libft/

clean :
	rm -rf $(OBJECTS)
	make -C libft/ clean

fclean : clean
	rm -rf $(NAME)
	rm -rf libft/$(LIBFT)

re : fclean all

lem_in.o : lem_in.c $(HEADER)
	$(CC) $(CFLAGS) -c lem_in.c $(HEADER)

aug_lib.o : aug_lib.c $(HEADER)
	$(CC) $(CFLAGS) -c aug_lib.c $(HEADER)

validate_ants.o : validate_ants.c $(HEADER)
	$(CC) $(CFLAGS) -c validate_ants.c $(HEADER)
