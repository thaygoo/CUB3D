/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_PTF.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:51:27 by huburton          #+#    #+#             */
/*   Updated: 2025/04/24 14:40:08 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex_ptf(unsigned int number, char type)
{
	int	rtn;
	int	tmp;

	rtn = 0;
	if (number >= 16)
	{
		tmp = ft_puthex_ptf(number / 16, type);
		if (tmp < 0)
			return (-1);
		rtn += tmp;
	}
	if (type == 'X')
		tmp = ft_putchar_ptf("0123456789ABCDEF"[number % 16]);
	if (type == 'x')
		tmp = ft_putchar_ptf("0123456789abcdef"[number % 16]);
	if (tmp < 0)
		return (-1);
	return (rtn + 1);
}
