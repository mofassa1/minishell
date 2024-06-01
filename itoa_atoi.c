/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:59:14 by afadouac          #+#    #+#             */
/*   Updated: 2024/03/21 02:33:11 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(long n)
{
	int	i;

	i = 1;
	while (n / 10 > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	set(long nb, int n, char *c, int s)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		c[0] = '-';
		i++;
	}
	c[s] = '\0';
	s--;
	while (s >= i)
	{
		c[s] = nb % 10 + '0';
		nb = nb / 10;
		s--;
	}
}

char	*ft_itoa(int n)
{
	long	nb;
	int		s;
	char	*c;

	s = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		s++;
	}
	s += count(nb);
	c = malloc(s + 1);
	if (!c)
		return (NULL);
	set(nb, n, c, s);
	return (c);
}

int	ft_atoi(const char *str)
{
	int		s;
	long	n;

	n = 0;
	s = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		s = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		n *= 10;
		n += *str - '0';
		str++;
	}
	return (n * s);
}
