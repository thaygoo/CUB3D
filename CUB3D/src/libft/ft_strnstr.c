/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hburton <hburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:32:50 by hburton           #+#    #+#             */
/*   Updated: 2023/06/13 13:23:36 by hburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *c1, const char *c2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!c1 && len == 0)
		return (0);
	if (!*c2)
		return ((char *)c1);
	while (c1[i] && i < len)
	{
		j = 0;
		while (c1[i + j] == c2[j] && (i + j) < len)
		{
			if (!c2[j + 1])
				return ((char *)c1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
