/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:06 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:37:07 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_voider(int signal)
{
	int	i;
	int	j;

	g_arg.input_ctl = 1;
	if (g_arg.pipe_count == -1)
	{
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
	else if (g_arg.pipe_count > -1)
	{
		i = -1;
		while (++i < g_arg.pipe_count + 1)
		{
			j = -1;
			while (++j < g_arg.cmds[i]->tmp_hdcount)
				if (g_arg.cmds[i]->heredoc[j].pid == 0)
					kill(g_arg.cmds[i]->heredoc[j].pid, SIGUSR2);
			if (g_arg.pid[i] == 0)
				kill(g_arg.pid[i], SIGUSR2);
		}
		write(1, "\n", 1);
	}
	g_arg.exit_status = 1;
	(void)signal;
}

void	eof_control(char *line)
{
	if (!line)
	{
		write(1, "\033[2D", 4);
		write(1, "\033[0mexit\n", 9);
		exit(0);
	}
}

void	sigquit_voider(int signal)
{
	(void)signal;
	if (g_arg.quit_flag == 1)
	{
		write(1, "\033[2D", 4);
		write(1, "  ", 2);
		write(1, "\033[2D", 4);
		g_arg.quit_flag = 0;
	}
	g_arg.quit_flag = 1;
}

void	signal_handler(int signal)
{
	g_arg.sigusr_i++;
	if (signal == SIGUSR1)
		g_arg.cmds[g_arg.sigusr_i - 1]->tmp_hdcount = 0;
}

void	child_signal_handler(int signal)
{
	if (signal == SIGUSR2)
		exit(0);
}
