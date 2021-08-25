/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 21:25:19 by alecasti          #+#    #+#             */
/*   Updated: 2021/08/09 21:43:05 by alecasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	create_func_array(funcPtr *func)
{
	int		i;

	i = 0;
	while (i < 256)
		func[i++] = &four_oh_four;
	func['c'] = &put_char;
	func['s'] = &put_str;
	func['p'] = &put_ptr;
	func['d'] = &put_nbr;
	func['i'] = &put_nbr;
	func['u'] = &put_nbr;
	func['x'] = &put_nbr;
	func['X'] = &put_nbr;
	func['%'] = &put_percent;
}

void	create_base_table(int *tab)
{
	ft_memset(tab, 0, sizeof(*tab));
	tab['d'] = 10;
	tab['i'] = 10;
	tab['u'] = 10;
	tab['x'] = 16;
	tab['X'] = 16;
}
