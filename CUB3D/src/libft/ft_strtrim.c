/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hburton <hburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:48:51 by hburton           #+#    #+#             */
/*   Updated: 2023/05/16 15:35:39 by hburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	k = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (k > i && ft_strchr(set, s1[k - 1]))
		k--;
	str = (char *)malloc(sizeof(char) * (k - i + 1));
	if (str == NULL)
		return (NULL);
	while (i < k)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
