/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:18:19 by tde-nico          #+#    #+#             */
/*   Updated: 2022/01/26 11:09:59 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef struct s_flags
{
	int		zero;
	int		left;
	int		hash;
	int		sign;
	int		space;
	int		width;
	int		precision;
	int		length_h;
	int		length_hh;
	int		length_l;
	int		length_ll;
	char	type;
}	t_flags;

void	ft_putunbr_base(unsigned long nbr, char *base);
int		ft_countunbr_base(unsigned long nbr, char *base);
void	add_filling(char char_fill, int size, int *len);
int		count_numbers(const char *str);
int		count_digits_unsig(unsigned int n);
int		count_digits_sig(int n, int include_sign);
int		fill_size_sing_int(t_flags *flags, int number);
int		parse_flags(const char *format, t_flags *flags);
int		parse_width(const char *format, va_list args, t_flags *flags);
int		parse_precision(const char *format, va_list args, t_flags *flags);
int		parse_length(const char *format, t_flags *flags);
int		parse_type(const char *format, t_flags *flags);
void	process_flags(int *len, va_list args, t_flags *flags);
void	process_char(int *len, va_list args, t_flags *flags);
void	process_string(int *len, va_list args, t_flags *flags);
void	process_pointer(int *len, va_list args, t_flags *flags);
void	process_signed_decimal(int *len, va_list args, t_flags *flags);
void	process_signed_decimal_2(int *len, int number, t_flags *flags, int s);
void	process_unsigned_decimal(int *len, va_list args, t_flags *flags);
void	process_unsigned_hex_low(int *len, va_list args, t_flags *flags);
void	process_unsigned_hex_up(int *len, va_list args, t_flags *flags);
void	process_percentage(int *len, t_flags *flags);
int		ft_printf(const char *format, ...);

#endif
