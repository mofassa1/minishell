NAME = minishell

LIB = -L /Users/afadouac/readline/lib

CFLAGS = -Wall -Wextra -Werror

PC = minishell.c ft_split.c helpers.c list.c lexer.c list_parser.c list_strings.c helpers3.c\
helpers2.c syntax.c errors.c garbage_collector.c parsing.c list_cmd.c execution.c env.c list_env.c\
helpers4.c cd.c files_opener.c expander.c itoa_atoi.c env_methode.c expander_helpers1.c\
expander_helpers2.c removers.c pwd.c export.c unset.c echo.c builtins.c bonus.c bonus_check.c\
wildcard.c wildcard_helpers.c env2.c str_functions.c here_doc.c expande_list.c\
cmd_for_exic.c files_opener2.c signals.c remouvers2.c wildcard_strs.c exit_status.c exit.c \
export_helpers.c

PO = ${PC:.c=.o}

all : ${NAME}

${NAME} : ${PO}
	${CC} ${CFLAGS} $^ -o $@ -lreadline $(LIB)

clean :
	${RM} ${PO}


fclean : clean
	${RM} ${NAME}

re : fclean all
