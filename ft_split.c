/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstupar <fstupar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:13:54 by fstupar           #+#    #+#             */
/*   Updated: 2022/04/25 14:03:03 by fstupar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_point
{
	int	i;
	int	g;
	int	f;
	int	z;
}	t_point;

static int	len_double(char const *str, char sep)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		while (str[i] == sep && str[i])
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != sep && str[i])
			i++;
		result++;
	}
	result++;
	return (result);
}

static int	len_single(char const *s, char c, t_point a)
{
	int	g;

	g = 0;
	while (s[a.i] != c && s[a.i] != '\0')
	{
		a.i++;
		g++;
	}
	g++;
	return (g);
}

static char	**split(char **array, char const *s, char c, t_point a)
{
	char	*string;

	while (s[a.i] != '\0')
	{
		if (s[a.i] != c)
		{
			a.z = len_single(s, c, a);
			string = (char *)malloc(sizeof(char) * a.z);
			if (string == NULL)
				return (NULL);
			while (s[a.i] != c && s[a.i] != '\0')
				string[a.g++] = s[a.i++];
			string[a.g] = '\0';
			a.g = 0;
			array[a.f++] = string;
		}
		else
			a.i++;
	}
	array[a.f] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	t_point	a;
	char	**array;
	int		k;
	k = len_double(s, c);
	array = (char **)malloc(sizeof(char *) * k);
	if (array == NULL)
		return (NULL);
	a.i = 0;
	a.g = 0;
	a.f = 0;
	a.z = 0;
	array = split(array, s, c, a);
	return (array);
}