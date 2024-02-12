/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:58:31 by muyumak           #+#    #+#             */
/*   Updated: 2022/11/09 17:58:31 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenofn(int n)
{
	int	i;

	if (n == 0)
		i = 2;
	else if (n > 0)
		i = 1;
	else
		i = 2;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*write_min_int(char *str, int *n, int *i)
{
	int	number;

	number = *n;
	str[0] = (-(number % 10) + 1) + 48;
	*n = *n / 10;
	*i = 1;
	return (str);
}

static char	*writenumber(char *str, int n)
{
	int	i;
	int	number;

	i = 0;
	number = n;
	if (number < 0)
	{
		if (n == -2147483648)
		{
			n += 1;
			write_min_int(str, &n, &i);
		}
		n *= -1;
	}
	while (n != 0)
	{
		str[i++] = (n % 10) + 48;
		n /= 10;
	}
	if (number < 0)
		str[i++] = '-';
	if (number == 0)
		str[i++] = 48;
	str[i] = 0;
	return (str);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		lenstr;
	char	change;

	i = 0;
	lenstr = ft_strlen(str);
	while (str[i] && i < lenstr / 2)
	{
		change = str[i];
		str[i] = str[lenstr - i - 1];
		str[lenstr - i - 1] = change;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		lenn;
	char	*str;
	int		number;

	number = n;
	lenn = lenofn(n);
	str = malloc(sizeof(char) * lenn);
	if (!str)
		return (0);
	str = writenumber(str, number);
	str = ft_strrev(str);
	return (str);
}
