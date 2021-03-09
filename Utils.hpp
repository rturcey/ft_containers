/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 09:40:30 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/09 10:20:37 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace	ft
{
	template<class It, class Itbis>
	bool	inf(It beg, It itend, Itbis beg2, Itbis itend2)
	{
		while (beg != itend && beg2 != itend2)
		{
			if (*beg < *beg2)
				return (1);
			else if (*beg > *beg2)
				return (-1);
			beg++;
			beg2++;
		}
		return (0);
	}
}

#endif
