/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:48 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:49 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	equal_control(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '=')
			return (0);
	return (1);
}

void	ft_smart_putstr(char **strings)
{
	int	i;
	int	j;

	i = -1;
	while (strings[++i])
	{
		j = -1;
		printf("declare -x ");
		while (strings[i][++j])
		{
			if (strings[i][j] == '=')
				printf("=\"");
			else
				printf("%c", strings[i][j]);
		}
		if (!equal_control(strings[i]))
			printf("%c", 34);
		printf("\n");
	}
}

void	set_export(void)
{
	int	variable_count;
	int	i;

	variable_count = split_len(g_arg.env);
	g_arg.exports = malloc(sizeof(char *) * (variable_count + 1));
	i = -1;
	while (g_arg.env[++i])
		g_arg.exports[i] = ft_strdup(g_arg.env[i]);
	g_arg.exports[i] = 0;
}
