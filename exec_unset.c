/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:45 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:35:48 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_env(char *value)
{
	int		index;
	int		len;
	int		i;
	int		j;
	char	**temp;

	index = check_envp(value);
	if (index == -1)
		return ;
	len = split_len(g_arg.env);
	temp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (i == index)
			j++;
		temp[i] = ft_strdup(g_arg.env[++j]);
	}
	temp[i] = 0;
	free_split(g_arg.env);
	g_arg.env = temp;
}

void	ft_delete_export(char *value)
{
	int		index;
	int		len;
	int		i;
	int		j;
	char	**temp;

	index = check_export(value);
	if (index == -1)
		return ;
	len = split_len(g_arg.exports);
	temp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (i == index)
			j++;
		temp[i] = ft_strdup(g_arg.exports[++j]);
	}
	temp[i] = 0;
	free_split(g_arg.exports);
	g_arg.exports = temp;
}

void	exec_unset(void)
{
	int	len;
	int	i;

	len = split_len(g_arg.cmds[0]->cmd_args);
	i = 0;
	while (++i < len)
	{
		ft_delete_export(g_arg.cmds[0]->cmd_args[i]);
		ft_delete_env(g_arg.cmds[0]->cmd_args[i]);
	}
}
