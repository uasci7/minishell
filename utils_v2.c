/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:11 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:37:13 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(int x)
{
	if (x != 0)
		return (0);
	printf("exit\n");
	if (split_len(g_arg.cmds[0]->cmd_args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		g_arg.exit_status = 1;
	}
	else if (split_len(g_arg.cmds[0]->cmd_args) == 2)
	{
		x = -1;
		while (g_arg.cmds[0]->cmd_args[1][++x])
		{
			if (!ft_isdigit(g_arg.cmds[0]->cmd_args[1][x]))
			{
				printf("minishell: %s: numeric argument required\n",
					g_arg.cmds[0]->cmd_args[1]);
				exit(255);
			}
		}
		exit(ft_atoi(g_arg.cmds[0]->cmd_args[1]));
	}
	else if (split_len(g_arg.cmds[0]->cmd_args) == 1)
		exit (0);
	return (0);
}

int	spreader(void)
{
	t_arg_list	*temp;
	int			j;
	int			i;

	temp = g_arg.list;
	g_arg.pid = malloc(sizeof(pid_t) * (g_arg.pipe_count + 1));
	if (g_arg.pipe_count > 0)
		open_pipes();
	g_arg.commands = malloc(sizeof(char **) * (g_arg.pipe_count + 2));
	j = -1;
	while (temp)
	{
		i = 0;
		g_arg.commands[++j] = malloc(sizeof(char *)
				* (count_cmd_arg(temp) + 1));
		if (spreader_v2(&temp, j))
			break ;
	}
	g_arg.commands[j + 1] = NULL;
	if (spreader_v3())
		return (1);
	return (0);
}
