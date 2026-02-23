/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hburton <hburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:33:16 by hburton           #+#    #+#             */
/*   Updated: 2023/06/13 13:20:46 by hburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;
	size_t	mult;

	mult = count * size;
	if (size != 0 && mult / size != count)
		return (0);
	pt = malloc(mult);
	if (pt == NULL)
		return (NULL);
	ft_bzero(pt, mult);
	return (pt);
}
