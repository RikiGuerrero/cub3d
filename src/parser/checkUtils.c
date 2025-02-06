/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:00:58 by rguerrer          #+#    #+#             */
/*   Updated: 2025/02/06 13:03:54 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_elements(char *input, int *elements)
{
	if (ft_strstr(input, "NO") != NULL)
		return (elements[0]++, 0);
	else if (ft_strstr(input, "SO") != NULL)
		return (elements[1]++, 0);
	else if (ft_strstr(input, "WE") != NULL)
		return (elements[2]++, 0);
	else if (ft_strstr(input, "EA") != NULL)
		return (elements[3]++, 0);
	else if (ft_strstr(input, "F") != NULL)
		return (elements[4]++, 0);
	else if (ft_strstr(input, "C") != NULL)
		return (elements[5]++, 0);
	return (1);
}
