GREEN			=	"\033[0;32m"
BLUE			=	"\033[0;36m"
END				=	"\033[0;0m"

SRCS		=		main.c minishell_exec.c utils_signal.c utils_v2.c utils_list.c \
					list_initializer.c utils_modified.c utils_format.c spreader_utils.c \
					pipe_process.c spreader.c set_s_cmd.c fd_settings.c error_check.c \
					get_env.c exec_echo.c exec_export.c exec_cd.c  heredoc_settings.c \
					exec_unset.c spreader_utils_v2.c utils_export.c

LIBFT		=		libft/libft.a

OBJS		=		$(SRCS:.c=.o)

NAME		=		minishell

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror

RM			=		rm -rf

all:		$(NAME) 


$(NAME):		$(OBJS) $(LIBFT)
				$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -lreadline -o $(NAME)

clean:
				$(RM) $(OBJS)
				make clean -C ./libft
$(LIBFT):
			make bonus -C ./libft

fclean:
				$(RM) $(OBJS) $(NAME)
				make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re