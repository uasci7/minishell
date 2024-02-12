/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:51 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:53 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_special(char c)
{
	if (c == ' ' || c == 9 || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	*get_env_var(char *str, char **env, int *i, int *j)
{
	int	index;
	int	len;

	index = 0;
	if (str[index] == '?')
	{
		*i += 1;
		return (ft_itoa(g_arg.exit_status));
	}
	while (ft_isalnum(str[index]))
		index++;
	*j = *i;
	*i += index;
	len = *i - *j;
	while (*env)
	{
		if (ft_strncmp(str, *env, len) == 0 && (*env)[len] == '=')
			break ;
		env++;
	}
	if (!(*env))
		return (NULL);
	return (ft_strdup(&((*env)[len + 1])));
}
