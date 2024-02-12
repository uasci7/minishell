/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:52 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:35:55 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_checker(int fd, char *filename)
{
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", filename);
		g_arg.exit_status = 1;
		return (1);
	}
	return (0);
}

int	fd_flags(t_arg_list **temp, int i)
{
	if ((*temp)->flag == 'i')
	{
		g_arg.cmds[i]->infile_name = (*temp)->content;
		g_arg.cmds[i]->fd_in = open((*temp)->content, O_RDONLY);
		if (fd_checker(g_arg.cmds[i]->fd_in, g_arg.cmds[i]->infile_name))
			return (1);
	}
	else if ((*temp)->flag == 't')
	{
		g_arg.cmds[i]->outfile_name = (*temp)->content;
		g_arg.cmds[i]->fd_out = open((*temp)->content,
				O_CREAT | O_TRUNC | O_RDWR, 0777);
	}
	else if ((*temp)->flag == 'p')
	{
		g_arg.cmds[i]->outfile_name = (*temp)->content;
		g_arg.cmds[i]->fd_out = open((*temp)->content,
				O_CREAT | O_APPEND | O_RDWR, 0777);
	}
	return (0);
}

int	set_fds(void)
{
	t_arg_list	*temp;
	int			i;

	i = -1;
	temp = g_arg.list;
	while (g_arg.cmds[++i] && temp)
	{
		if (temp->flag == '|' && temp->next != NULL)
			temp = temp->next;
		while (temp)
		{
			if (fd_flags(&temp, i))
				return (1);
			if (temp->flag == '|')
				break ;
			temp = temp->next;
		}
	}
	return (0);
}

void	inputinit(void)
{
	g_arg.input_ctl = 0;
	g_arg.input = readline("minishell$ ");
}
