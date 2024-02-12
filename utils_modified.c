/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_modified.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:01 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:37:04 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_v3(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*result;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (0);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	free(s1);
	free(s2);
	result[i] = '\0';
	return (result);
}

char	*ft_strdup_v2(char *str, int start, int end)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[start] && start < end)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_strlen_v2(char *str, char q, int i)
{
	while (str[i] && str[i] != q)
		i++;
	return (i);
}

char	*ft_strdup_v3(char *str, int *start, char end)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen_v2(str, end, *start) - *start;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[*start] && str[*start] != end)
	{
		result[i] = str[*start];
		i++;
		(*start)++;
	}
	result[i] = '\0';
	(*start)++;
	return (result);
}
