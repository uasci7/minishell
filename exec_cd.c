/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uasci <uasci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:27 by uasci             #+#    #+#             */
/*   Updated: 2023/09/29 15:35:29 by uasci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(void)
{
	char	*home;
	int		index;
	int		i;
	int		j;

	index = check_envp("HOME");
	home = malloc(sizeof(char) * (ft_strlen(g_arg.env[index] + 5) + 1));
	i = 4;
	j = -1;
	while (g_arg.env[index][++i])
		home[++j] = g_arg.env[index][i];
	home[j + 1] = 0;
	return (home);
}

void	exec_cd(void)
{
	char	*temp;

	if (((split_len(g_arg.cmds[0]->cmd_args) == 2
				&& !ft_strcmp("~", g_arg.cmds[0]->cmd_args[1]))
			|| split_len(g_arg.cmds[0]->cmd_args) == 1))
	{
		temp = get_home();
		if (is_available_path(temp))
			return ;
		free(temp);
	}
	else if (split_len(g_arg.cmds[0]->cmd_args) == 2)
	{
		if (g_arg.cmds[0]->cmd_args[1][0] == '~')
		{
			temp = ft_strjoin(get_variable("HOME"),
					&g_arg.cmds[0]->cmd_args[1][1]);
			is_available_path(temp);
			free(temp);
		}
		else
			if (is_available_path(g_arg.cmds[0]->cmd_args[1]))
				return ;
	}
}

int	is_available_path(char *path)
{
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

void	set_pwd(char *temp)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(cwd, PATH_MAX);
	temp = ft_strjoin("PWD=", cwd);
	if (check_envp(temp) != -1)
	{
		put_env(temp);
		put_export(temp);
	}
	g_arg.pwd = ft_strdup(temp + 4);
	free(temp);
	free(cwd);
}
