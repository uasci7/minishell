/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:30 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:37:32 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "./libft/libft.h"

typedef struct s_heredoc
{
	pid_t	pid;
	int		tubes[2];
	char	*here_doc_name;
	char	*input;
}	t_heredoc;

typedef struct s_arg_list
{
	char				*content;
	char				flag;
	struct s_arg_list	*next;
}	t_arg_list;

typedef struct s_cmd
{
	char			**cmd_args;
	char			*infile_name;
	char			*outfile_name;
	int				fd_in;
	int				fd_out;
	int				query;
	int				heredoc_count;
	int				tmp_hdcount;
	t_heredoc		*heredoc;
}	t_cmd;

struct s_arg
{
	pid_t		*pid;
	char		quote_flag;
	char		*input;
	char		*cmd;
	char		*pwd;
	char		*paths;
	char		**cmd_paths;
	char		**cmd_args;
	char		**args_temp;
	char		**env;
	char		**exports;
	char		***commands;
	int			quit_flag;
	int			arg_count;
	int			pipe_count;
	int			cmd_index;
	int			exit_status;
	int			sigusr_i;
	int			close_process;
	int			**tubes;
	int			input_ctl;
	t_cmd		**cmds;
	t_arg_list	*list;
}	g_arg;

char		*get_cmd(char **paths, char *cmd);
int			cmd_process(int i);
void		sigquit_voider(int signal);
void		eof_control(char *line);
void		sigint_voider(int signal);
void		ft_lstdelone_v2(t_arg_list **lst);
void		ft_lstclear_v2(t_arg_list **lst);
t_arg_list	*ft_lstnew_v2(char *content, char flag);
void		ft_lstadd_back_v2(t_arg_list **lst, t_arg_list *new);
int			list_init(char *str);
char		*ft_strjoin_v3(char *s1, char *s2);
char		*ft_strdup_v2(char *str, int start, int end);
char		*ft_strdup_v3(char *str, int *start, char end);
int			is_it_special(char c);
char		*get_env_var(char *str, char **env, int *i, int *j);
int			ft_strlen_v2(char *str, char q, int i);
void		count_arg(void);
void		refresh_counts(void);
int			spreader(void);
void		open_pipes(void);
int			count_cmd_arg(t_arg_list *temp);
int			flag_setter(void);
void		free_split(char **strings);
void		t_cmd_settings(void);
void		free_commands(void);
int			set_fds(void);
int			pipe_check(void);
void		set_tubes(void);
void		close_tubes(void);
void		wait_process(void);
void		close_fd(t_cmd *command);
void		get_env(char **envp);
int			split_len(char **strings);
void		exec_pwd(void);
int			executor(int i);
void		exec_echo(int j);
int			ft_strlen_equal(char *arg);
int			check_envp(char *value);
int			check_export(char *value);
void		exec_export(void);
int			equal_control(char *arg);
void		put_export(char *value);
void		put_env(char *value);
void		ft_smart_putstr(char **strings);
void		set_export(void);
void		exec_cd(void);
void		here_doc_process(t_cmd *command, int hd_id);
int			ft_strcmp(char *s1, char *s2);
void		count_heredoc(t_cmd *command);
void		set_heredocs(void);
void		open_heredoc(t_cmd *command);
void		close_heredoc_tubes(void);
void		close_other_heredocs(t_cmd *command);
t_arg_list	*last_of_list(void);
int			executor_v2(int i);
void		exec_unset(void);
int			check_quote(char *str);
char		*get_variable(char *str);
int			is_exportable(char *str, int len);
int			exec_exit(int x);
int			filename_control(void);
int			flag_setter_v2(t_arg_list **temp);
int			flag_setter_v3(t_arg_list **temp);
void		free_env(int *argc, char **argv);
void		inputinit(void);
void		child_signal_handler(int signal);
void		print_input(char **strings);
void		signal_handler(int signal);
void		set_pwd(char *temp);
int			is_available_path(char *path);
int			spreader_v2(t_arg_list **list, int j);
int			spreader_v3(void);

#endif