/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:54:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 10:14:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*joint_str;
	int			s1_len;
	int			s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joint_str = (char *)ft_memalloc(s1_len + s2_len + 1);
	ft_memmove(joint_str, s1, s1_len);
	ft_memmove(joint_str + s1_len, s2, s2_len + 1);
	return (joint_str);
}
