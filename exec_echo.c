/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:33 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:35:34 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(int j, int i)
{
	while (g_arg.cmds[j]->cmd_args[i])
	{
		printf("%s", g_arg.cmds[j]->cmd_args[i]);
		if (i < split_len(g_arg.cmds[j]->cmd_args) - 1)
			printf(" ");
		i++;
	}
}

int	check_echo_option(char *value)
{
	int	i;

	i = 0;
	if (value[0] != '-')
		return (1);
	while (value[++i])
		if (value[i] != 'n')
			return (1);
	return (0);
}

void	exec_echo(int j)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (g_arg.cmds[j]->cmd_args[i])
	{
		if (!check_echo_option(g_arg.cmds[j]->cmd_args[i]))
		{
			if (i == 1)
				flag = 1;
			i++;
		}
		else
			break ;
	}
	if (flag == 1)
		print_echo(j, i);
	else if (flag == 0)
	{
		print_echo(j, i);
		printf("\n");
	}
}
