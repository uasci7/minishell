/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:27 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:28 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(void)
{
	int	i;

	i = 0;
	g_arg.tubes = malloc(sizeof(int *) * g_arg.pipe_count);
	while (i < g_arg.pipe_count)
	{
		g_arg.tubes[i] = malloc(sizeof(int) * 2);
		pipe(g_arg.tubes[i]);
		i++;
	}
}

void	set_tubes(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count)
		g_arg.cmds[i]->fd_out = g_arg.tubes[i][1];
	i = 0;
	while (++i < g_arg.pipe_count + 1)
		g_arg.cmds[i]->fd_in = g_arg.tubes[i - 1][0];
}

void	close_tubes(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count)
	{
		close(g_arg.tubes[i][1]);
		close(g_arg.tubes[i][0]);
	}
	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		if (g_arg.cmds[i]->infile_name != 0)
			close(g_arg.cmds[i]->fd_in);
		if (g_arg.cmds[i]->outfile_name != 0)
			close(g_arg.cmds[i]->fd_out);
	}
}

void	close_fd(t_cmd *command)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count)
	{
		if (command->fd_in != g_arg.tubes[i][0])
			close(g_arg.tubes[i][0]);
		if (command->fd_out != g_arg.tubes[i][1])
			close(g_arg.tubes[i][1]);
	}
}

void	wait_process(void)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < g_arg.pipe_count + 1)
	{
		waitpid(g_arg.pid[i], &g_arg.exit_status, 0);
		if (WIFEXITED(g_arg.exit_status))
			g_arg.exit_status = WEXITSTATUS(g_arg.exit_status);
	}
}
