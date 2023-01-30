NAME=minishell
SRCS=exec_func/exec_func.c torkanizer/torkanizer.c\
		utils/strlcat.c utils/strlcpy.c utils/split.c\
		readline/readline.c
OBJS=$(SRCS:%.c=%.o)
cc=cc
CFLAGS= -Wall -Werror -Wextra
all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

debug:$(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address -fno-omit-frame-pointer $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all