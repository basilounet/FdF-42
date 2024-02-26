/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:42:41 by bvasseur          #+#    #+#             */
/*   Updated: 2023/11/27 18:04:10 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlentc(s1, 0);
	len_s2 = ft_strlentc(s2, 0);
	dest = ft_calloc(sizeof(char), len_s1 + len_s2 + 1);
	if (!dest)
		return (NULL);
	if (s1)
		ft_strncpy(dest, s1, len_s1 + 1);
	if (s2)
		ft_strncpy(dest + len_s1, s2, len_s2 + 1);
	return (dest);
}
