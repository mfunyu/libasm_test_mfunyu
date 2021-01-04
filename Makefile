# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 16:04:37 by mfunyu            #+#    #+#              #
#    Updated: 2021/01/04 14:19:20 by mfunyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libasm.a
SRCS := $(wildcard ../libasm/*.s)
OBJS := $(SRCS:.s=.o)
TARGET := exec

AR := ar rc
AS := nasm
CC := gcc
ASFLAGS = -fmacho64
CFLAGS := -Wall -Wextra -Werror

ifdef dbg
ASFLAGS += -g
ifeq ($(dbg), 1)
CFLAGS += -g -D STDOUT=2
else
CFLAGS += -fsanitize=address -D STDOUT=2
endif
endif

all: $(NAME)

# create library from .o
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# comple files with main
check: main.c $(OBJS)
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(OBJS)

# compile libasm with main
main: main.c $(NAME)
	$(CC) $(CFLAGS) -D STDOUT=2 -c main.c
	$(CC) $(CFLAGS) -D STDOUT=2 -o $(TARGET) main.o -L. -lasm


clean:
	$(RM) $(OBJS) main.o

fclean: clean
	$(RM) $(NAME) $(TARGET) *.log

re: fclean all

.PHONY: all clean fclean re
