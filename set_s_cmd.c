/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_s_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:31 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:33 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_cmd_settings(void)
{
	int			i;
	t_arg_list	*temp;

	temp = g_arg.list;
	g_arg.cmds = malloc(sizeof(t_cmd *) * (g_arg.pipe_count + 2));
	i = 0;
	while (i < g_arg.pipe_count + 1)
	{
		g_arg.cmds[i] = malloc(sizeof(t_cmd));
		g_arg.cmds[i]->infile_name = NULL;
		g_arg.cmds[i]->outfile_name = NULL;
		g_arg.cmds[i]->heredoc = NULL;
		g_arg.cmds[i]->heredoc_count = 0;
		g_arg.cmds[i]->tmp_hdcount = 0;
		g_arg.cmds[i]->cmd_args = g_arg.commands[i];
		g_arg.cmds[i]->fd_in = 0;
		g_arg.cmds[i]->fd_out = 1;
		i++;
	}
	g_arg.cmds[i] = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = -1;
	while (s1[++i])
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}

void	print_input(char **strings)
{
	int	i;

	i = -1;
	while (strings[++i])
		if (strings[i] != NULL)
			printf("%s\n", strings[i]);
}

void	free_split(char **strings)
{
	int	i;

	i = -1;
	while (strings[++i])
		free(strings[i]);
	free(strings);
}

t_arg_list	*last_of_list(void)
{
	t_arg_list	*temp;

	temp = g_arg.list;
	while (temp->next)
		temp = temp->next;
	temp->next = NULL;
	return (temp);
}
