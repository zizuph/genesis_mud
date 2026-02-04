#include "std.h"

object *members;

create_object()
{
  if (masterp())
    members = ({ });
  else
  {
    MASTER->add_member( TP );
    move( TP );
  }
}

void add_member( object member )
{
  if (masterp())
    members += ({ member });
  else
    throw( "Tried to call add_member in a clone." );
}

void init()
{
  if (!masterp())
      add_action( "line", "kalad" );
}

status line( string str )
{
  int c;

  for (c=0; c < sizeof( MASTER->query_members() ); c++)
    if (MASTER->query_members()[c])
      my_tell_object( MASTER->query_members()[c], "Kalad @ " + TP_N + ": " +
                                                  str );
    else
      MASTER->remove_member( c-- );
  return 1;
}

void remove_member( int index )
{
  if (!masterp())
    throw( "Tried to call remove_member in a clone." );
  if (index < 0 || index >= sizeof( members ))
    throw( "Index out of bounds in remove_object (index=" + index + ")" );
  members = members[ 0..index-1 ] + members[ index+1..MYCKE ];
}

object *query_members()
{
  if (!masterp())
    throw( "Called query_members in clone." );
  return members;
}

string query_auto_load()
{
  return MASTER;
}
