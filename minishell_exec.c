/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:22 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:24 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_process(t_cmd *command, int hd_id)
{
	char	*temp;

	command->heredoc[hd_id].pid = fork();
	if (command->heredoc[hd_id].pid == 0)
	{
		while (1)
		{
			if (hd_id == command->heredoc_count - 1)
				close(command->heredoc[hd_id].tubes[0]);
			command->heredoc[hd_id].input = readline("> ");
			if (ft_strcmp(command->heredoc[hd_id].input,
					command->heredoc[hd_id].here_doc_name) == 0
				|| g_arg.close_process == 1)
				exit (0);
			temp = ft_strjoin(command->heredoc[hd_id].input, "\n");
			if (hd_id == command->heredoc_count - 1)
				write(command->heredoc[hd_id].tubes[1], temp, ft_strlen(temp));
			free(command->heredoc[hd_id].input);
			free(temp);
		}
	}
}

void	open_heredoc(t_cmd *command)
{
	int	i;

	i = -1;
	while (++i < command->heredoc_count)
	{
		here_doc_process(command, i);
		if (i == command->heredoc_count - 1)
			close(command->heredoc[i].tubes[1]);
		wait(&command->heredoc[i].pid);
	}
	kill(0, SIGUSR1);
	i++;
}

void	waited_heredoc(int i)
{
	int	x;

	x = 1;
	while (x < i + 1)
	{
		if (i > 0 && g_arg.cmds[x - 1]->tmp_hdcount != 0)
			while (1)
				if (g_arg.cmds[x - 1]->tmp_hdcount == 0)
					break ;
		x++;
	}
	if (g_arg.cmds[i]->heredoc_count != 0)
		open_heredoc(g_arg.cmds[i]);
	else
		close_heredoc_tubes();
}

int	cmd_process(int i)
{
	g_arg.pid[i] = fork();
	if (g_arg.pid[i] == 0)
	{
		signal(SIGUSR2, child_signal_handler);
		waited_heredoc(i);
		close_fd(g_arg.cmds[i]);
		dup2(g_arg.cmds[i]->fd_in, STDIN_FILENO);
		dup2(g_arg.cmds[i]->fd_out, STDOUT_FILENO);
		if (!executor(i))
			exit(0);
		if (access(g_arg.cmds[i]->cmd_args[0], 0) != 0)
			g_arg.cmd = get_cmd(g_arg.cmd_paths, g_arg.cmds[i]->cmd_args[0]);
		else
			g_arg.cmd = g_arg.cmds[i]->cmd_args[0];
		if (!g_arg.cmd)
			exit(127);
		if (execve(g_arg.cmd, g_arg.cmds[i]->cmd_args, g_arg.env) == -1)
		{
			printf("minishell: %s: command not found\n",
				g_arg.cmds[i]->cmd_args[0]);
			exit(127);
		}
	}
	return (0);
}
