/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:45:21 by muyumak           #+#    #+#             */
/*   Updated: 2022/11/28 19:00:15 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pntr;

	pntr = (void *)malloc(count * size);
	if (!pntr)
		return (NULL);
	ft_bzero(pntr, size * count);
	return (pntr);
}
