/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstupar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:26:11 by fstupar           #+#    #+#             */
/*   Updated: 2021/10/20 11:33:44 by fstupar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 58 || c <= 47)
		return (0);
	else
		return (1);
}

/*
int main(void)
{
	char c = '8';
	printf("%d\n", ft_isdigit(c));
}*/