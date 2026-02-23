/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_w_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:51:58 by huburton          #+#    #+#             */
/*   Updated: 2025/04/24 14:40:08 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_w_space(char **strs, int count)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (i < count)
	{
		temp = result;
		result = ft_strjoin(result, strs[i]);
		free(temp);
		if (i < count - 1)
		{
			temp = result;
			result = ft_strjoin(result, " ");
			free(temp);
		}
		i++;
	}
	return (result);
}
