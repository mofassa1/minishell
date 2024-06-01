/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:57:53 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/04 23:23:27 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READLINE_LIBRARY

# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include "/Users/afadouac/readline/include/readline/readline.h"
# include "/Users/afadouac/readline/include/readline/history.h"

typedef enum s_tokens
{
	WORD,
	GREAT,
	LESS,
	GREATGREAT,
	LESSLESS,
	PIPE,
	AND,
	OR,
	LEFTP,
	RIGHTP
}						t_tokens;

typedef struct s_collect
{
	void				*ptr;
	struct s_collect	*next;
}						t_collect;

typedef struct s_lexer
{
	char				*str;
	t_tokens			token;
	char				*ori5inal;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_strings
{
	char				*str;
	t_tokens			type;
	int					fd;
	int					here_fd;
	struct s_strings	*next;
}						t_strings;

typedef struct s_parser
{
	char				*cmd;
	t_strings			*flags;
	t_strings			*infile;
	t_strings			*outfile;
	struct s_parser		*next;
	struct s_parser		*prev;
}						t_parser;

typedef struct s_cmd
{
	char				*cmd;
	char				*path;
	char				**flags;
	pid_t				pid;
	t_strings			*infiles;
	t_strings			*outfiles;
	int					infile;
	int					outfile[2];
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_env
{
	char				*variable;
	char				*content;
	struct s_env		*next;
}						t_env;

char					**ft_split(char *str, char *charset);
int						check_quoting(char *str, int a);
t_lexer					*ft_lstnew(char *word, t_tokens t);
void					ft_lstadd_back(t_lexer **lst, t_lexer *new);
size_t					ft_strlen(const char *s);
size_t					new_lenght1(char *s);
size_t					new_lenght2(char *s);
t_lexer					*lexer(char *s);
void					ft_putstr_fd(char *s, int fd);
int						ft_strcmp(const char *s1, const char *s2);
t_lexer					*spaces_separator(char *s);
t_tokens				tokenizer(char *s);
int						syntax_p_a_o(t_lexer *node);
int						syntax_of_redirection(t_lexer *node);
int						syntax_p(t_lexer *node);
int						error_printer(t_lexer *tmp);
void					*ft_malloc(size_t size, char job);
t_parser				*ft_lstnew_parser(void);
char					*ft_strdup(const char *s1);
t_strings				*ft_lstnew_strings(char *str, t_tokens t);
void					ft_lstadd_back_strings(t_strings **lst, t_strings *new);
void					ft_lstadd_back_parser(t_parser **lst, t_parser *new);
t_parser				*parser(t_lexer *to_parse);
int						is_rediretion(t_lexer *l);
void					redirection_here(t_parser *cmd, t_lexer *node);
t_cmd					*ft_lstnew_cmd(t_parser *parsed);
char					**sts(t_strings *s, char *cmd);
void					ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int						executer(t_parser *parsed);
char					*ft_strtrim(char *s);
size_t					ft_lstsize_strings(t_strings *lst);
void					env_init(char **env);
void					env_lstadd_back(t_env **lst, t_env *new);
char					*cmd_path(char *cmd);
t_env					*get_env(char *var);
int						ft_cd(t_cmd *cmd);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
void					infile_o(t_cmd *cmd);
t_strings				*ft_lstlast_strings(t_strings *lst);
void					outfile_o(t_cmd *cmd);
void					close_files(t_cmd *cmds);
char					*cmd_path(char *cmd);
char					**env_to_str(void);
int						env_lstsize(t_env *lst);
void					expander(t_lexer *to_parse);
t_env					*get_env(char *var);
int						nbr_of_quote(char *s);
char					*ft_itoa(int n);
int						set_env_content(t_env *env, char *s);
void					error_p(char *s);
char					*expande(char *s, int fex);
char					*get_env_content(char *var);
void					copy(char *new, char *s, int *j);
char					*variable_name_geter(char *s);
int						ft_isdigit(int c);
int						allowed_char(char c);
int						is_expandeable(char *s, int a, int fex);
int						dollar_check(char *s);
void					remove_usless_dollars(t_lexer *to_parse);
void					ambiguous(t_lexer **to_parse);
void					ft_echo(t_cmd *cmd);
void					ft_pwd(void);
int						ft_unset(t_cmd *cmd);
int						ft_export(t_cmd *cmd);
char					*ft_strchr(const char *s, int c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						builtin_cmds(t_cmd *cmd, char **env);
int						check_builtin(char *s);
void					ft_env(char **env);
int						logic_gate(char *new);
int						traitement(t_lexer *to_parse);
int						ft_atoi(const char *str);
int						ft_export_only(void);
int						is_it_btw_parenthes(t_lexer *h);
int						expande_size(char *s, int fex);
t_lexer					*wildcard(t_lexer *h);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					*ft_strjoin_or(char const *s1, char const *s2);
t_lexer					*ft_lst_last(t_lexer **lst);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
int						espaces_check(char *str);
void					env_init_null(void);
int						ft_int_strchr(char *str, char c);
t_env					*ft_env_new(char *variable, char *content);
char					*ft_strdup_original(const char *s1);
size_t					quote_counter(char *s, char ch);
int						nbr_of_quoting_before(char *str, int a, char q);
char					*ft_strchr(const char *s, int c);
t_env					*ft_lstnew_env(char *name, char *content);
void					ft_clear_cmd(t_env **new);
int						here_doc_opener(t_cmd *cmd);
void					error_of_exit(char *cmd);
int						star_check(t_lexer *h);
int						ft_strrchr(const char *s, int c);
char					*ft_strchr(const char *s, int c);
void					check_here_doc_limite(t_cmd *cmds);
int						here_couter(t_strings *infile);
t_cmd					*create_cmds(t_parser *parsed);
void					quote_remover(t_parser *parsed);
void					quote_remover_strings(t_strings *s);
void					handle_sigint(int sig);
char					*remove_dollars(char *s);
int						strings_count(char **str);
int						ft_strrcmp(char *str1, char *str2, int len1, int len2);
int						is_sorted(char *str, char *cmd, char *file);
int						is_doubled(int *str, int i);
int						sorted(int *arr, int i);
void					open_all_infiles(t_strings *infile);
void					open_all_outfiles(t_strings *outfile);
int						size(char *s);
int						c_increase(t_tokens t);
int						syntax_of_w(t_lexer **h);
void					here_doc(char *delimiter, int fd);
void					ft_close(int fd);
void					open_here_doc(t_cmd *cmd);
unsigned int			*get_exit_stat(void);
char					**get_pwdpath(void);
void					set_pwdpath(char *str);
int						*ctrl_c(void);
int						*cd_dp(void);
void					env_clear(void);
void					set_values(char **env);
void					safi_rah_salina(int exit_value);
int						ft_exit(char **flags);
char					**sort_str(char **str);
char					**fill_array(void);
void					set__value(t_cmd *cmds);
void					run_in_parent(t_cmd *cmds);
int						add_nodes_in(t_lexer *new_nodes,
							t_lexer **h, t_lexer *prev, t_lexer *next);
int						are_all_stars(char *str);
void					sort_lex(t_lexer **lex);
t_env					**get_env_list(void);
int						c_word(char *str, char *charset);
t_lexer					*lexer_copy(t_lexer *h, t_lexer *limite);
t_lexer					*expande_list(t_lexer *h);
t_lexer					*dup_lexer_node(t_lexer *node);
#endif