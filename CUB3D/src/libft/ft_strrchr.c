/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hburton <hburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:31:43 by hburton           #+#    #+#             */
/*   Updated: 2023/05/16 16:06:28 by hburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	int		occ;
	char	ch;
	char	*str;

	str = (char *)s;
	ch = (char)c;
	i = 0;
	occ = -1;
	while (i <= ft_strlen((char *)str))
	{
		if (str[i] == ch)
			occ = i;
		i++;
	}
	if (occ != -1)
		return ((char *)str + occ);
	return (NULL);
}
