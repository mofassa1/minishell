/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:50:54 by afadouac          #+#    #+#             */
/*   Updated: 2024/04/02 23:22:09 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd_oldpwd(char *oldwd, char *cwd)
{
	if (cwd)
	{
		set_pwdpath(cwd);
		set_env_content(get_env("PWD"), cwd);
	}
	set_env_content(get_env("OLDPWD"), oldwd);
	if (!oldwd && !cwd)
		*cd_dp() += 1;
	else
		*cd_dp() = 0;
}

char	*ft_get_cwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		ft_putstr_fd("cd : ", 2);
		perror(NULL);
	}
	return (str);
}

int	ft_chdir(char *dest)
{
	char	*oldwd;
	char	*cwd;

	oldwd = ft_strdup_original(*get_pwdpath());
	if (!(*get_pwdpath()))
		oldwd = ft_strdup_original("");
	if (!ft_strcmp(dest, "HOME"))
	{
		dest = get_env_content("HOME");
		if (!dest)
		{
			ft_putstr_fd("mini: cd: HOME not set\n", 2);
			return (free(oldwd), 1);
		}
	}
	if (chdir(dest))
	{
		free(oldwd);
		ft_putstr_fd("mini: cd: ", 2);
		perror(dest);
		return (1);
	}
	cwd = ft_get_cwd();
	set_pwd_oldpwd(oldwd, cwd);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	if (!cmd->flags[1])
		return (ft_chdir("HOME"));
	else
		return (ft_chdir(cmd->flags[1]));
}
