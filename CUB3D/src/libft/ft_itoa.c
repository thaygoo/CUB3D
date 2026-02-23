/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hburton <hburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:46:56 by hburton           #+#    #+#             */
/*   Updated: 2023/06/13 12:22:28 by hburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_length(int n)
{
	int		i;
	int		neg;

	neg = 0;
	i = 1;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + neg + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		length;
	int		neg;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = ft_itoa_length(n);
	str = (char *)malloc(sizeof(*str) * length);
	if (str == NULL)
		return (NULL);
	str[--length] = '\0';
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	while (length--)
	{
		str[length] = (n % 10) + '0';
		n = n / 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
