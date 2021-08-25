/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 21:04:18 by alecasti          #+#    #+#             */
/*   Updated: 2021/08/21 22:39:34 by alecasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

typedef struct		s_pf
{
	const char	*str;
	va_list		list;

	char		item;
}					t_pf;

typedef void		(*funcPtr)(t_pf*);

int		ft_printf(const char *str, ...);

void	parse_char(t_pf *obj);
void	create_func_array(funcPtr *func);

void	four_oh_four(t_pf *obj);
void	put_percent(t_pf *obj);
void	put_ptr(t_pf *obj);
void	put_upper_hexa_nbr(t_pf *obj);
void	put_lower_hexa_nbr(t_pf *obj);
void	put_unsigned_nbr(t_pf *obj);
void	put_signed_nbr(t_pf *obj);
void	put_str(t_pf *obj);
void	put_char(t_pf *obj);

char	*create_hex_array(char specifier);
void	ft_puthexa(unsigned int num, char *str);
void	ft_puthexa_long(unsigned long long int num, char *str);
void	ft_putnbr(int num);
void	ft_putnbr_unsigned(unsigned int num);
void	ft_putchar(char c);
int		is_lower(int c);


#endif
