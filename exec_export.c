/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:40 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:35:41 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_envp(char *value)
{
	int	i;

	i = -1;
	while (g_arg.env[++i])
	{
		if (ft_strlen_equal(g_arg.env[i]) == ft_strlen_equal(value))
			if (!ft_strncmp(g_arg.env[i], value, ft_strlen_equal(g_arg.env[i])))
				return (i);
	}
	return (-1);
}

int	check_export(char *value)
{
	int	i;

	i = -1;
	while (g_arg.exports[++i])
	{
		if (ft_strlen_equal(g_arg.exports[i]) == ft_strlen_equal(value))
			if (!ft_strncmp(g_arg.exports[i],
					value, ft_strlen_equal(g_arg.exports[i])))
				return (i);
	}
	return (-1);
}

void	exec_export(void)
{
	int	i;
	int	len;

	len = split_len(g_arg.cmds[0]->cmd_args);
	i = 0;
	while (++i < len)
	{
		if (is_exportable(g_arg.cmds[0]->cmd_args[i],
				ft_strlen_equal(g_arg.cmds[0]->cmd_args[i])))
		{
			put_export(g_arg.cmds[0]->cmd_args[i]);
			if (!equal_control(g_arg.cmds[0]->cmd_args[i]))
				put_env(g_arg.cmds[0]->cmd_args[i]);
		}
		else
			printf("minishell: export: %s: not a valid identifier\n",
				g_arg.cmds[0]->cmd_args[i]);
	}
}

void	put_export(char *value)
{
	char	**temp;
	int		i;
	int		index;

	index = check_export(value);
	if (index == -1)
	{
		temp = malloc(sizeof(char *) * (split_len(g_arg.exports) + 2));
		i = -1;
		while (g_arg.exports[++i])
			temp[i] = ft_strdup(g_arg.exports[i]);
		temp[i] = ft_strdup(value);
		temp[++i] = 0;
		free_split(g_arg.exports);
		g_arg.exports = temp;
	}
	else
	{
		if (!equal_control(value))
		{
			free(g_arg.exports[index]);
			g_arg.exports[index] = ft_strdup(value);
		}
	}
}

void	put_env(char *value)
{
	char	**temp;
	int		len;
	int		i;
	int		index;

	index = check_envp(value);
	if (index == -1)
	{
		len = split_len(g_arg.env);
		temp = malloc(sizeof(char *) * (len + 2));
		i = -1;
		while (g_arg.env[++i])
			temp[i] = ft_strdup(g_arg.env[i]);
		temp[i] = ft_strdup(value);
		temp[++i] = 0;
		free_split(g_arg.env);
		g_arg.env = temp;
	}
	else
	{
		free(g_arg.env[index]);
		g_arg.env[index] = ft_strdup(value);
	}
}
