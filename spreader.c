/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:45 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:45 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(int i)
{
	if (!ft_strcmp("env", g_arg.cmds[i]->cmd_args[0]))
	{
		print_input(g_arg.env);
		return (0);
	}
	else if (!ft_strcmp("pwd", g_arg.cmds[i]->cmd_args[0]))
	{
		printf("%s\n", g_arg.pwd);
		return (0);
	}
	else if (!ft_strcmp("echo", g_arg.cmds[i]->cmd_args[0]))
	{
		exec_echo(i);
		return (0);
	}
	else if (!ft_strcmp("export", g_arg.cmds[i]->cmd_args[0]))
	{
		if (split_len(g_arg.cmds[i]->cmd_args) == 1)
			ft_smart_putstr(g_arg.exports);
		return (0);
	}
	return (1);
}

int	executor_v2(int i)
{
	if (!ft_strcmp("export", g_arg.cmds[0]->cmd_args[0]))
	{
		if (split_len(g_arg.cmds[i]->cmd_args) > 1)
			exec_export();
		else
			return (1);
		return (0);
	}
	else if (!ft_strcmp("cd", g_arg.cmds[0]->cmd_args[0]))
	{
		exec_cd();
		return (0);
	}
	else if (!ft_strcmp("unset", g_arg.cmds[0]->cmd_args[0]))
	{
		if (split_len(g_arg.cmds[0]->cmd_args) > 1)
			exec_unset();
		else
			return (2);
		return (0);
	}
	else if (!ft_strcmp("exit", g_arg.cmds[i]->cmd_args[0]))
		if (!exec_exit(i))
			return (0);
	return (1);
}

int	spreader_v2(t_arg_list **list, int j)
{
	int	i;

	i = 0;
	while (*list)
	{
		if ((*list)->flag == 'o')
			g_arg.commands[j][i++] = ft_strdup((*list)->content);
		if ((*list)->flag == '|')
			break ;
		(*list) = (*list)->next;
	}
	g_arg.commands[j][i] = 0;
	if ((*list))
	{
		if ((*list)->flag == '|')
		{
			if ((*list)->next)
				(*list) = (*list)->next;
			else
				return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	spreader_v3(void)
{
	int	i;

	t_cmd_settings();
	set_tubes();
	if (set_fds())
		return (1);
	set_heredocs();
	i = -1;
	while (++i < g_arg.pipe_count + 1)
		if (executor_v2(i) == 1)
			cmd_process(i);
	close_heredoc_tubes();
	close_tubes();
	wait_process();
	return (0);
}
