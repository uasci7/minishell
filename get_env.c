/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:58 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:01 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_len(char **strings)
{
	int	i;

	if (!strings)
		return (-1);
	i = 0;
	while (strings[i])
		i++;
	return (i);
}

char	*get_variable(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (g_arg.env[++i])
		if (!ft_strncmp(str, g_arg.env[i], len))
			return (g_arg.env[i] + len + 1);
	return (0);
}

void	get_env(char **envp)
{
	int	len;
	int	i;

	len = split_len(envp);
	g_arg.env = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (envp[++i])
		g_arg.env[i] = ft_strdup(envp[i]);
	g_arg.env[i] = 0;
}

void	exec_pwd(void)
{
	int	i;

	i = -1;
	while (g_arg.env[++i])
	{
		if (!ft_strncmp("PWD", g_arg.env[i], 3))
			printf("%s\n", g_arg.env[i]);
	}
}
