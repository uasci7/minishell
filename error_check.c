/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:22 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:35:25 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(void)
{
	t_arg_list	*last;

	last = g_arg.list;
	if (last == NULL)
		return (1);
	while (last->next)
		last = last->next;
	if (last->flag == '|')
	{
		printf("minishell: syntax error near unexpected token %s\n",
			last->content);
		return (1);
	}
	return (0);
}

int	check_quote(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
			{
				return (1);
			}
		}
	}
	return (0);
}

int	is_exportable(char *str, int len)
{
	int	i;

	if (!ft_isalpha(*str))
		return (0);
	i = -1;
	while (str[++i] && i < len)
	{
		if (!ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

int	filename_control_v2(void)
{
	t_arg_list	*temp;

	temp = last_of_list();
	if (temp->flag == '>' || temp->flag == '<' || temp->flag == '|')
	{
		printf("minishell: syntax error near unexpected token %s\n",
			temp->content);
		return (1);
	}
	return (0);
}

int	filename_control(void)
{
	t_arg_list	*temp;

	temp = g_arg.list;
	while (temp)
	{
		if (temp->flag == '<' || temp->flag == '>')
		{
			if (!ft_strcmp("<", temp->content) || !ft_strcmp(">", temp->content)
				|| !ft_strcmp("<<", temp->content)
				|| !ft_strcmp(">>", temp->content)
				|| !ft_strcmp("|", temp->content))
			{
				printf("minishell: syntax error near unexpected token %s\n",
					temp->content);
				return (1);
			}
		}
		temp = temp->next;
	}
	if (filename_control_v2())
		return (1);
	return (0);
}
