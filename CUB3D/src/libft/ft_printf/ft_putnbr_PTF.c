/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_PTF.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:52:21 by huburton          #+#    #+#             */
/*   Updated: 2025/04/04 13:56:43 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_ptf(long int nbr)
{
	char	*str;
	int		rtn;

	str = ft_itoa_ptf(nbr);
	if (!str)
		return (-1);
	rtn = ft_putstring_ptf(str);
	free(str);
	return (rtn);
}
