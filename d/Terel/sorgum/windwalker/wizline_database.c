#include "std.h"

#define SAVE_FILE (SAVE_DIR + "wizline_database")

mapping channels;
static mapping users;
/*
 * ([ lowercase channel-name : ({ channel-name, ({ users, ... }), openp,
 *				  creator }), ... ])
 */
#define CHANNELS_NAME 0
#define CHANNELS_USERS 1
#define CHANNELS_OPENP 2
#define CHANNELS_CREATOR 3

create_object()
{
  if (!masterp())
  {
    "/secure/master"->do_debug("destroy", TO);
    throw( "The wizline_database may not be cloned." );
  }
  users = ([ ]);
  channels = ([ ]);
  seteuid( getuid() );
  restore_object( SAVE_FILE );
}

void add_me()
{ users[ TP_N ] = TP; }

void remove_me()
{ users = m_delete( users, TP_N ); }

status add_channel( string name, int openp )
{
  if (channels[ lower_case( name ) ])
    MY_NOTIFY_FAIL( "There is already a channel named " + name + "." );
  if (member_array( lower_case( name ), query_domain_list() ) != -1)
    MY_NOTIFY_FAIL( "A channel may not have the same name as a domain." );
  channels[ lower_case( name ) ] = ({ name, ({ TP_N }), openp, TP_N });
  save_object( SAVE_FILE );
  return 1;
}

status join_channel( string channel )
{
  channel = lower_case( channel );
  if (!channels[ channel ])
    MY_NOTIFY_FAIL( "There is no channel named " + channel + "." );
  if (member_array( TP_N, channels[ channel ][ CHANNELS_USERS ] ) != -1)
    MY_NOTIFY_FAIL( "You are already listening to the channel " + channel +
		    "." );
  if (!channels[ channel ][ CHANNELS_OPENP ])
    MY_NOTIFY_FAIL( "That channel is closed." );
  channels[ channel ][ CHANNELS_USERS ] += ({ TP_N });
  save_object( SAVE_FILE );
  return 1;
}

status leave_channel( string channel )
{
  channel = lower_case( channel );
  if (!channels[ channel ])
    MY_NOTIFY_FAIL( "There is no channel named " + channel + "." );
  if (member_array( TP_N, channels[ channel ][ CHANNELS_USERS ] ) == -1)
    MY_NOTIFY_FAIL( "You are not listening to the channel " + channel + "." );
  if (channels[ channel ][ CHANNELS_CREATOR ] == TP_N)
    channels = m_delete( channels, channel );
  else
    channels[ channel ][ CHANNELS_USERS ] -= ({ TP_N });
  save_object( SAVE_FILE );
  return 1;
}

status add_user( string user, string channel )
{
  channel = lower_case( channel );
  user = Capitalize( user );
  if (channels[ channel ][ CHANNELS_CREATOR ] != TP_N)
    MY_NOTIFY_FAIL( "You are not the creator of that channel." );
  if (member_array( user, channels[ channel ][ CHANNELS_USERS ] ) != -1)
    MY_NOTIFY_FAIL( user + "is already listening to the channel " +
		    channel + "." );
  channels[ channel ][ CHANNELS_USERS ] += ({ user });
  save_object( SAVE_FILE );
  return 1;
}

status remove_user( string user, string channel )
{
  channel = lower_case( channel );
  user = Capitalize( user );
  if (channels[ channel ][ CHANNELS_CREATOR ] != TP_N)
    MY_NOTIFY_FAIL( "You are not the creator of that channel." );
  if (member_array( user, channels[ channel ][ CHANNELS_USERS ] ) != -1)
    MY_NOTIFY_FAIL( user + "is not listening to the channel " + channel +
		    "." );
  channels[ channel ][ CHANNELS_USERS ] -= ({ user });
  save_object( SAVE_FILE );
  return 1;
}

string list_channels()
{
  int c;
  string result;

  result = "";
  for (c=0; c < sizeof( m_values( channels ) ); c++)
    result += m_values( channels )[c][ CHANNELS_NAME ] + " (" +
      (m_values( channels )[c][ CHANNELS_OPENP ] ? "open" : "closed") +
      ") creator " + m_values( channels )[c][ CHANNELS_CREATOR ] + ".\n";
  return result;
}

mixed list_channel( string channel )
{
  int c;
  string result;
  string *tmp, *tmp2;
  
  channel = lower_case( channel );
  if (!channels[ channel ])
    MY_NOTIFY_FAIL( "There is no channel named " + channel + "." );
  tmp = channels[ channel ][ CHANNELS_USERS ][0..MYCKE];
  if (!channels[ channel ][ CHANNELS_OPENP ] &&
      member_array( TP_N, tmp ) == -1)
    MY_NOTIFY_FAIL( "You are not a member of that closed channel." );
  tmp2 = tmp & (string *)m_indices( users );
  tmp -= tmp2;
  for (c=0; c < sizeof( tmp ); c++)
    tmp[c] = "(" + tmp[c] + ")";
  tmp = tmp2 + tmp;
  result = tmp[0];
  for (c=1; c < sizeof( tmp ) - 1; c++)
    result += ", " + tmp[c];
  if (sizeof( tmp ) > 1)
    result += " and " + tmp[ sizeof( tmp ) - 1 ];
  return my_line_wrap( result + "." );
}

status send( string channel, string msg )
{
  int c;
  mixed tmp;

  channel = lower_case( channel );
  if ((tmp = member_array( Capitalize( channel ), query_domain_list() )) != -1)
  {
    channel = Capitalize( channel );
    if (query_wiz_dom( TP_N ) != channel)
      MY_NOTIFY_FAIL( "You are not a member of the domain " + channel + "." );
    my_tell_domain( channel, channel + " @ " + TP_N + ": " + msg );
    return 1;
  }
  if (!channels[ channel ])
    MY_NOTIFY_FAIL( "There is no channel named " + channel + "." );
  tmp = channels[ channel ][ CHANNELS_USERS ];
  if (member_array( TP_N, tmp ) == -1)
    MY_NOTIFY_FAIL( "You are not listening to the channel " + channel + "." );
  tmp &= m_indices( users );
  for (c=0; c < sizeof( tmp ); c++)
    if (!users[ tmp[c] ])
      users = m_delete( users, tmp[c] );
    else
      my_tell_object( users[ tmp[c] ], channels[ channel ][ CHANNELS_NAME ] +
		      " @ " + TP_N + ": " + msg );
  return 1;
}
