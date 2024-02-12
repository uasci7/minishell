/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:05 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:06 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_heredoc(t_cmd *command)
{
	static t_arg_list	*temp;
	int					i;

	i = 0;
	if (temp == NULL)
		temp = g_arg.list;
	while (temp && temp->flag != '|')
	{
		if (temp->flag == 'h')
			command->heredoc_count++;
		temp = temp->next;
	}
	if (temp && temp->flag == '|' && temp->next != NULL)
		temp = temp->next;
	command->tmp_hdcount = command->heredoc_count;
}

void	set_heredoc_name(void)
{
	t_arg_list	*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	temp = g_arg.list;
	while (temp)
	{
		if (temp->flag == 'e')
		{
			g_arg.cmds[i]->heredoc[j].here_doc_name = ft_strdup(temp->content);
			j++;
		}
		if (temp->flag == '|')
		{
			i++;
			j = 0;
		}
		temp = temp->next;
	}
}

void	close_heredoc_tubes(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		if (g_arg.cmds[i]->heredoc_count > 0)
		{
			close(g_arg.cmds[i]->heredoc
			[g_arg.cmds[i]->heredoc_count - 1].tubes[0]);
			close(g_arg.cmds[i]->heredoc
			[g_arg.cmds[i]->heredoc_count - 1].tubes[1]);
		}
	}
}

void	close_other_heredocs(t_cmd *command)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		if (g_arg.cmds[i]->heredoc != command->heredoc)
		{
			close(g_arg.cmds[i]->heredoc
			[g_arg.cmds[i]->heredoc_count - 1].tubes[1]);
			close(g_arg.cmds[i]->heredoc
			[g_arg.cmds[i]->heredoc_count - 1].tubes[0]);
		}
	}
}

void	set_heredocs(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		count_heredoc(g_arg.cmds[i]);
		if (g_arg.cmds[i]->heredoc_count > 0)
		{
			g_arg.cmds[i]->heredoc
				= malloc(sizeof(t_heredoc) * g_arg.cmds[i]->heredoc_count);
			pipe(g_arg.cmds[i]->heredoc[
				g_arg.cmds[i]->heredoc_count - 1].tubes);
			g_arg.cmds[i]->fd_in = g_arg.cmds[i]->heredoc
			[g_arg.cmds[i]->heredoc_count - 1].tubes[0];
		}
	}
	set_heredoc_name();
}
