#pragma once

#include <stdlib.h>
#include <unistd.h>

int		ret_free( int ret, char* ptr );
int		ret_err_message( const int ret, const char *message );
int		ft_strlen( const char *str );
int		ft_strcmp( const char *str1, const char *str2 );
int		ft_strncmp( const char *str1, const char *str2, const int len );
void	ft_putstr_fd( const char *str, int fd );
char	*ft_strdup( const char *str );
char	*ft_strjoin_f( char *str1, char *str2, const int free_arg );
char	**ft_split( const char *str, const char *charset );
