/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:47:33 by alecasti          #+#    #+#             */
/*   Updated: 2021/08/21 22:38:59 by alecasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_lower(int c)
{
	if (c >= 141 && c <= 172)
		return (c);
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int num)
{
	unsigned int	new_num;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	new_num = num;
	if (new_num >= 10)
		ft_putnbr(new_num / 10);
	ft_putchar((new_num % 10) + '0');
}

void	ft_putnbr_unsigned(unsigned int num)
{
	unsigned int	new_num;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	new_num = num;
	if (new_num >= 10)
		ft_putnbr(new_num / 10);
	ft_putchar((new_num % 10) + '0');
}

void	ft_puthexa_long(unsigned long long int num, char *str)
{
	unsigned long long int	new_num;
	
	new_num = num;
	if (new_num >= 16)
		ft_puthexa((new_num / 16), str);
	ft_putchar(str[(new_num % 16)]);
}

void	ft_puthexa(unsigned int num, char *str)
{
	unsigned int	new_num;
	
	new_num = num;
	if (new_num >= 16)
		ft_puthexa((new_num / 16), str);
	ft_putchar(str[(new_num % 16)]);
}

char	*create_hex_array(char specifier)
{
	int		i;
	char	*str;

	str = (char *)malloc(sizeof(char) * 17);
	if (!str)
		return (NULL);
	str[16] = '\0';
	i = -1;
	while (++i < 10)
		str[i] = '0' + i;
	while (i > 9 && i < 16)
	{
		if (specifier == 'x')
			str[i] = 'a' + (i - 10);
		else
			str[i] = 'A' + (i - 10);
		i++;
	}
	
	return (str);
}

/* -c- */
void	put_char(t_pf *obj)
{
	int		item;

	item = va_arg(obj->list, int);
	if (item == '\0' || !item)
		ft_putchar(0);
	else
		ft_putchar(item);
	// ITOA that bish -- int -> char before write
}

/* -s- */
void	put_str(t_pf *obj)
{
	char	*str;
	int		i;

	str = va_arg(obj->list, char *);
	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
		i++;
	write(1, str, i);
}

/* -d i- */
void	put_signed_nbr(t_pf *obj)
{
	int		i;

	i = va_arg(obj->list, int);
	if (!i && i != 0)
		return ;
	// TODO -- check that i is within signed limits
	// -2147483648 < i < 2147483647
	ft_putnbr(i);
}

/* -u- */
void	put_unsigned_nbr(t_pf *obj)
{
	unsigned int		i;

	i = va_arg(obj->list, unsigned int);
	if (!i && i != 0)
		return ;
	/**
	 * DO A CHECK? -- throw error or exception or catch
	if (i < 0 || i > 4294967295)
		return ;
	 * THEN send the number to putnbr because certain no errors
	***/
	ft_putnbr_unsigned(i);
}

/* -x- */
void	put_lower_hexa_nbr(t_pf *obj)
{
	unsigned int	i;
	char			*str;

	i = va_arg(obj->list, unsigned int);
	str = create_hex_array('x');
	// DO A CHECK HERE TOO ?  -- min and max necessary?
	ft_puthexa(i, str);
	// TODO is this where I free ?
	free(str);

}

/* -X- */
void	put_upper_hexa_nbr(t_pf *obj)
{
	unsigned int	i;
	char			*str;

	i = va_arg(obj->list, unsigned int);
	str = create_hex_array('X');
	// DO A CHECK HERE TOO ?  -- min and max necessary?
	ft_puthexa(i, str);
	// TODO is this where I free ?
	free(str);
}

/* -p- */
void	put_ptr(t_pf *obj)
{
	void	*p;
	char	*str;

	p = va_arg(obj->list, void *);
	// x == 170 && X == 130
	str = create_hex_array('x');
	// send to # conversion and then x conversion
	write(1, "0x", 2);
	ft_puthexa_long((unsigned long long int)p, str);
	free(str);
	
}

/* -%- */
void	put_percent(t_pf *obj)
{
	// twice because one % got me here in the first place
	//ft_putchar('%');
	ft_putchar(obj->item);
	// is there anything to do here ??
}

/* -404- */
void	four_oh_four(t_pf *obj)
{
	printf("this aint doing shit! Here's a char -- %c\n", obj->item);
}

void	create_func_array(funcPtr *func)
{
	int		i;

	i = 0;
	while (i < 256)
		func[i++] = &four_oh_four;
	func['c'] = &put_char;
	func['s'] = &put_str;
	func['p'] = &put_ptr;
	func['d'] = &put_signed_nbr;
	func['i'] = &put_signed_nbr;
	func['u'] = &put_unsigned_nbr;
	func['x'] = &put_lower_hexa_nbr;
	func['X'] = &put_upper_hexa_nbr;
	func['%'] = &put_percent;
}

void	parse_char(t_pf *obj)
{
	funcPtr		func[256];
	//int			table[256];

	create_func_array(func);
	//create_base_table(table);
	
	obj->item = *obj->str;
	func[(unsigned char)obj->item](obj);
	obj->str++;
}

int		ft_printf(const char *str, ...)
{
	t_pf	details;
	int		i;

	i = 0;
	details.str = str;
	va_start(details.list, str);
	while (*details.str && details.str[i])
	{
		if (*details.str == '%')
		{
			++details.str;
			parse_char(&details);
		}
		else
			write(1, (details.str)++, 1);
	}
	va_end(details.list);

	return (1);
}
