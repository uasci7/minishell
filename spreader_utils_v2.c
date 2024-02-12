/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader_utils_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:36:37 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:36:38 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_setter_v2(t_arg_list **temp)
{
	if (ft_strcmp((*temp)->content, "<<") == 0 && (*temp)->flag == '<')
	{
		(*temp)->flag = 'h';
		if ((*temp)->next && (*temp)->next->flag == 'i')
			(*temp)->next->flag = 'e';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	if (ft_strcmp((*temp)->content, ">>") == 0 && (*temp)->flag == '>')
	{
		(*temp)->flag = 'a';
		if ((*temp)->next && (*temp)->next->flag == 't')
			(*temp)->next->flag = 'p';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	return (0);
}

int	flag_setter_v3(t_arg_list **temp)
{
	if ((*temp)->flag == '>')
	{
		if ((*temp)->next && (*temp)->next->flag == 'o')
			(*temp)->next->flag = 't';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	if ((*temp)->flag == '<')
	{
		if ((*temp)->next && (*temp)->next->flag == 'o')
			(*temp)->next->flag = 'i';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	return (0);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	if (cmd == NULL)
		return (0);
	if (paths == NULL || *cmd == '\0')
	{
		printf("minishell: %s: command not found\n", cmd);
		return (0);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	printf("minishell: %s: command not found\n", cmd);
	return (0);
}
