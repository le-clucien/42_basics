
#define BUFFER_SIZE 10

#include <unistd.h>
#include <stdio.h>
#include "utils.h"

char		*get_next_line( const int fd )
{
	static char	*storage;
	int			read_ret;
	int			len_to_endline;
	char		*line;
	char		buf[ BUFFER_SIZE + 1 ];

	// FILL STORAGE untill end of line
	while ( 1 )
	{
		read_ret = read( fd, buf, BUFFER_SIZE );
		if ( read_ret == -1 )
			return NULL;
		buf[ read_ret ] = '\0';

		if ( storage )
			storage = ft_strjoin_f( storage, buf, 1 );
		else
			storage = ft_strdup( buf );

		if ( ft_strchr( storage, '\n' ) || read_ret != BUFFER_SIZE )
			break ;
	}

	// FILL LINE
	// If end of file
	if ( read_ret == 0 )
	{
		line = ft_strdup( storage );
		if ( storage )
			ret_free( 0, storage );
	}
	// If end of line
	else
	{
		len_to_endline = ft_strslen( storage, "\n" );
		line = ft_strndup( storage, len_to_endline );
		storage = ft_substr_f( storage, len_to_endline + 1, 1 ); // +1 is to go after \n
	}

	return ( read_ret ? line : NULL );
}