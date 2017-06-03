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
			construct_destruct.o \
			aug_lib.o \
			validate_ants.o \
			read_rooms1.o \
			read_rooms2.o \
			check_room_commands.o \
			validate_coords_create_storage.o \
			read_links1.o \
			read_links2.o \
			finding_path.o \
			sorting_routes.o \
			set_search.o \
			moving_ants.o \
			creating_nodes.o \
			free1.o \
			free2.o \
			norme1.o \

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

construct_destruct.o : construct_destruct.c $(HEADER)
	$(CC) $(CFLAGS) -c construct_destruct.c $(HEADER)

aug_lib.o : aug_lib.c $(HEADER)
	$(CC) $(CFLAGS) -c aug_lib.c $(HEADER)

validate_ants.o : validate_ants.c $(HEADER)
	$(CC) $(CFLAGS) -c validate_ants.c $(HEADER)

read_rooms1.o : read_rooms1.c $(HEADER)
	$(CC) $(CFLAGS) -c read_rooms1.c $(HEADER)

read_rooms2.o : read_rooms2.c $(HEADER)
	$(CC) $(CFLAGS) -c read_rooms2.c $(HEADER)

check_room_commands.o : check_room_commands.c $(HEADER)
	$(CC) $(CFLAGS) -c check_room_commands.c $(HEADER)

validate_coords_create_storage.o : validate_coords_create_storage.c $(HEADER)
	$(CC) $(CFLAGS) -c validate_coords_create_storage.c $(HEADER)

read_links1.o : read_links1.c $(HEADER)
	$(CC) $(CFLAGS) -c read_links1.c $(HEADER)

read_links2.o : read_links2.c $(HEADER)
	$(CC) $(CFLAGS) -c read_links2.c $(HEADER)

finding_path.o : finding_path.c $(HEADER)
	$(CC) $(CFLAGS) -c finding_path.c $(HEADER)

sorting_routes.o : sorting_routes.c $(HEADER)
	$(CC) $(CFLAGS) -c sorting_routes.c $(HEADER)

set_search.o : set_search.c $(HEADER)
	$(CC) $(CFLAGS) -c set_search.c $(HEADER)

moving_ants.o : moving_ants.c $(HEADER)
	$(CC) $(CFLAGS) -c moving_ants.c $(HEADER)

creating_nodes.o : creating_nodes.c $(HEADER)
	$(CC) $(CFLAGS) -c creating_nodes.c $(HEADER)

free1.o : free1.c $(HEADER)
	$(CC) $(CFLAGS) -c free1.c $(HEADER)

free2.o : free2.c $(HEADER)
	$(CC) $(CFLAGS) -c free2.c $(HEADER)

norme1.o : norme1.c $(HEADER)
	$(CC) $(CFLAGS) -c norme1.c $(HEADER)
