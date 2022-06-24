#include "utils.h"
#include <stdio.h>

// --------------------------------------------------------------------- //
//                               RETURNS                                 //
// --------------------------------------------------------------------- //

/**
 * @brief returns given int after freeing pointer
 * 
 * @param ret 
 * @param ptr 
 * @return int 
 */
int		ret_free( int ret, char* ptr )
{
	free( ptr );
	ptr = NULL;
	return ret;
}

/**
 * @brief print message to stderr and returns ret
 * 
 * @param ret
 * @param message 
 * @return int 
 */
int		ret_err_message( const int ret, const char *message )
{
	ft_putstr_fd( message, STDERR_FILENO );
	return ret;
}

// --------------------------------------------------------------------- //
//                            STRINGS RELATED                            //
// --------------------------------------------------------------------- //

/**
 * @brief return length of given string
 * 
 * @param str 
 * @return int 
 */
int	ft_strlen( const char *str )
{
	int	len = 0;

	while ( str[ len ] )
		len++;
	return len;
}

/**
 * @brief return nb of char between index 0 of str and end_str
 * 
 * @param str 
 * @param end_str
 * @return int 
 */
int	ft_strslen( const char *str, const char *end_str )
{
	int	len = 0;
	int	end_str_len = ft_strlen( end_str );

	while ( str[ len ] && ft_strncmp( str + len, end_str, end_str_len ) )
		len++;
	return len;
}


/**
 * @brief returns 0 if both strings are the same, diff otherwise
 * 
 * @param str1 
 * @param str2 
 * @return int 
 */
int		ft_strcmp( const char *str1, const char *str2 )
{
	int	i = 0;

	while ( str1[ i ] && str2[ i ] )
	{
		if ( str1[ i ] != str2[ i ] )
			return str1[ i ] - str2[ i ];
		i++;
	}
	return 0;
}

/**
 * @brief returns 0 if both first len characters of the strings are the same, diff otherwise
 * 
 * @param str1 
 * @param str2 
 * @param len
 * @return int 
 */
int		ft_strncmp( const char *str1, const char *str2, const int len )
{
	int	i = 0;

	while ( str1[ i ] && str2[ i ] && i < len )
	{
		if ( str1[ i ] != str2[ i ] )
			return str1[ i ] - str2[ i ];
		i++;
	}
	return 0;
}

/**
 * @brief write given string to file descriptor
 * 
 * @param str
 * @param fd 
 */
void	ft_putstr_fd( const char *str, const int fd )
{
	write( fd, str, ft_strlen( str ) );
}

/**
 * @brief allocates and return a copy of a given string
 * 
 * @param str 
 * @return char* 
 */
char	*ft_strdup( const char *str )
{
	char	*new_str;
	int	i = 0;

	new_str = malloc( sizeof( char ) * ( ft_strlen( str ) + 1 ) );
	if ( !new_str )
		return NULL;

	do
	{
		new_str[ i ] = str[ i ];
	} while ( str[ ++i ] );
	new_str[ i ] = '\0';

	return new_str;
}


/**
 * @brief allocate and fill a string composed of str1 followed by str2.
 * 
 * @param str1 
 * @param str2 
 * @param free_arg
 * 		if 1: free str1 before return, if 2: free str2, if 3: free both strings, else : do nothing
 * @return char*
 */
char	*ft_strjoin_f( char *str1, char *str2, const int free_arg )
{
	char	*new_str;
	int		new_i = 0;
	int		i;

	new_str = malloc( sizeof( char ) * ( ft_strlen( str1 ) + ft_strlen( str2 ) + 1 ) );
	if ( !new_str )
		return NULL;
	
	i = 0;
	while ( str1[ i ] )
		new_str[ new_i++ ] = str1[ i++ ];
	i = 0;
	while ( str2[ i ] )
		new_str[ new_i++ ] = str2[ i++ ];
	new_str[ new_i ] = '\0';

	if ( free_arg == 1 || free_arg == 3 )
		free( str1 );
	if ( free_arg == 2 || free_arg == 3 )
		free( str2 );

	return new_str;
}

/**
 * @brief allocate and returns an array of strings. Those strings are copies of each substring in str.
 * 		Substring are seperated by separator.
 * 
 * @param str 
 * @param separator
 * @return char** 
 */
char	**ft_split( const char *str, const char *separator )
{
	const int	sep_len = ft_strlen( separator );
	char		**array;
	int			words_count;
	int			word_len;
	int			i;

	// COUNT WORDS
	i = 0;
	words_count = 0;
	while ( str[ i ] )
	{
		while ( !ft_strncmp( str + i, separator, sep_len ) )
			i += sep_len;
		if ( i >= ft_strlen( str ) )
			break ;
		words_count++;
		while ( ft_strncmp( &str[i], separator, sep_len ) )
			++i;
	}

	// ALLOCATE ARRAY
	array = malloc( sizeof( char * ) * ( words_count + 1 ) );
	if ( !array )
		return NULL;

	// FILL WITH STRINGS
	i = 0;
	words_count = 0;
	while ( str[ i ] )
	{
		while ( !ft_strncmp( str + i, separator, sep_len ) )
			i += sep_len;
		if ( i >= ft_strlen( str ) )
			break ;

		word_len = ft_strslen( str + i, separator );
		array[ words_count ] = malloc( sizeof( char ) * ( word_len + 1 ) );
		if ( !array[ words_count ] )
			return NULL;

		word_len = 0;
		while ( ft_strncmp( str + i, separator, sep_len ) )
			array[ words_count ][ word_len++ ] = str[ i++ ];
		array[ words_count ][ word_len ] = '\0';
		++words_count;
	}

	// DEFINE END OF ARRAY
	array[ words_count ] = NULL;

	return array;
}
