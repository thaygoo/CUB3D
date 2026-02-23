/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstring_PTF.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:42:43 by huburton          #+#    #+#             */
/*   Updated: 2025/04/24 14:40:08 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstring_ptf(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (ft_putstring_ptf("(null)"));
	while (str[len])
	{
		if (ft_putchar_ptf(str[len]) < 0)
			return (-1);
		len++;
	}
	return (len);
}
