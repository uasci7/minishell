/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:35:03 by muyumak           #+#    #+#             */
/*   Updated: 2022/11/14 23:02:17 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	straightmatch(char s, char const *set)
{
	size_t	i;
	int		control;

	i = 0;
	control = 0;
	while (set[i])
	{
		if (s == set[i])
			control = 1;
		i++;
	}
	return (control);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && straightmatch(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && straightmatch(s1[end - 1], set))
		end--;
	result = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!result)
		return (0);
	i = 0;
	while (start < end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = 0;
	return (result);
}
