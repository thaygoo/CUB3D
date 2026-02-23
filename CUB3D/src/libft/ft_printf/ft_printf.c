/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:14:25 by huburton          #+#    #+#             */
/*   Updated: 2025/04/24 14:40:08 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_type(va_list args, const char type)
{
	if (type == '%')
		return (ft_putchar_ptf('%'));
	else if (type == 'c')
		return (ft_putchar_ptf(va_arg(args, int)));
	else if (type == 's')
		return (ft_putstring_ptf(va_arg(args, char *)));
	else if (type == 'p')
		return (ft_putpointer_ptf(va_arg(args, unsigned long int), 1));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr_ptf(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putunint_ptf(va_arg(args, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (ft_puthex_ptf(va_arg(args, unsigned int), type));
	return (-1);
}

static int	ft_check_str(const char *str, int *mi, va_list args)
{
	int	format;
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			format = ft_type(args, str[i]);
			if (format == -1)
				return (-1);
			*mi += format;
		}
		else
		{
			format = ft_putchar_ptf(str[i]);
			if (format == -1)
				return (-1);
			*mi += format;
		}
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;

	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	if (ft_check_str(str, &i, args) == -1)
		return (-1);
	va_end(args);
	return (i);
}
