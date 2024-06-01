/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezzine <mezzine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:57:59 by mezzine           #+#    #+#             */
/*   Updated: 2024/04/03 07:05:26 by mezzine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_space_adder(char *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = ft_malloc((new_lenght1(s) + 1) * sizeof(char), 'm');
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<')
			&& !check_quoting(s, i))
		{
			new[j++] = ' ';
			new[j++] = s[i];
			if (s[i + 1] == s[i])
				new[j++] = s[++i];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*second_space_adder(char *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = ft_malloc((new_lenght2(s) + 1) * sizeof(char), 'm');
	while (s[i])
	{
		if ((s[i] == ')' || s[i] == '('
				|| (s[i] == '&' && s[i + 1] == '&')) && !check_quoting(s, i))
		{
			new[j++] = ' ';
			if (s[i] == '&')
				new[j++] = s[i++];
			new[j++] = s[i];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*space_adder(char *s)
{
	char	*s1;
	char	*s2;

	s1 = first_space_adder(s);
	s2 = second_space_adder(s1);
	return (s2);
}

int	traitement(t_lexer *to_parse)
{
	t_parser	*parsed;

	expander(to_parse);
	to_parse = wildcard(to_parse);
	ambiguous(&to_parse);
	to_parse = expande_list(to_parse);
	parsed = parser(to_parse);
	return (executer(parsed));
}

int	main(int ac, char **av, char **env)
{
	char		*s;
	char		*new;

	(void)av;
	if (ac > 1)
		return (0);
	set_values(env);
	while (1)
	{
		s = readline("mini$ ");
		if (!s)
			break ;
		new = space_adder(s);
		*ctrl_c() = 1;
		logic_gate(new);
		ft_malloc(0, 'f');
		if (*s)
			add_history(s);
		free(s);
		*ctrl_c() = 0;
	}
	ft_putstr_fd("exit\n", 1);
	safi_rah_salina(*get_exit_stat());
	return (0);
}
