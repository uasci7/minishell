/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:19:14 by muyumak           #+#    #+#             */
/*   Updated: 2022/11/12 21:25:52 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*last;
	void	*content;

	last = 0;
	if (!lst || !f || !del)
		return (0);
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			del(content);
			ft_lstdelone(last, del);
			return (0);
		}
		ft_lstadd_back(&last, ft_lstnew(content));
		lst = lst->next;
	}
	return (last);
}
