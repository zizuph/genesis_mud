#include "std.h"
#define DATABASE (HOME + "objs/wizline_database.c")

create_object()
{
  if (masterp())
    return;
  seteuid( getuid() );
  DATABASE->add_me();
/*  seteuid( 0 ); The day we get really paranoid */
  set_long( my_line_wrap( 
"This is the multi-channel wizline object. It can be used in the following " +
"ways:\n" +
"   wiz[channel] [message], to send a message to the specified channel. You " +
"must have joined that channel in order to send messages to it.\n" +
"   wiz[your domain] [message], to send a message to all wizards in your " +
"domain.\n" +
"   join channel [name of channel], to join an open channel.\n" +
"   leave channel [name of channel], to leave a channel. If the creator " +
"leaves a channel that channel will be removed.\n" +
"   create open channel [name of channel], to create a open channel.\n" +
"   create closed channel [name of channel], to create a closed channel. " +
"You cannot join a closed channel, the creator must add all listeners.\n" +
"   add [name of player] to [name of channel], as a creator you may add " +
"listeners to your channel.\n" +
"   remove [name of player] from [name of channel], as a creator you may " +
"remove listeners from your channel.\n" +
"   list channels, will show all existing channels.\n" +
"   list channel [name of channel], will show all listening to that " +
"channel.\n" ) );
  set_short( "multi-channel wizline-object (good stuff!)" );
  add_name( "wizline" );
  add_name( "wizline-object" );
  move( TP );
}

void init()
{
  if (masterp())
    return;
  /* following 4 lines added by metaquazi 930418 */
  if(environment() &&
     environment() == this_player() &&
     !this_player()->query_wiz_level())
      remove_object();
  add_action( "send", "wiz", 1 );
  add_action( "list", "list" );
  add_action( "join", "join" );
  add_action( "leave", "leave" );
  add_action( "create_channel", "create" );
  add_action( "add", "add" );
  add_action( "remove", "remove" );
}

status send( string str )
{ return DATABASE->send( query_verb()[3..MYCKE], str ); }
  
status list( string str )
{
  string channel;
  mixed tmp;

  if (!stringp( str ))
    return 0;
  if (str == "channels")
    if (tmp = DATABASE->list_channels())
      write( tmp );
    else
      return 0;
  else if (sscanf( str, "channel %s", channel ) &&
	   sscanf( channel, "%s %s", str, str ) != 2)
    if (tmp = DATABASE->list_channel( channel ))
      write( tmp );
    else
      return 0;
  else
    MY_NOTIFY_FAIL( "Usage: list channels.\n    or list channel [name]." );
  return 1;
}

status join( string str )
{
  string channel;

  if (!stringp( str ))
    return 0;
  if (sscanf( str, "channel %s", channel ) &&
      sscanf( channel, "%s %s", str, str ) != 2)
    return DATABASE->join_channel( channel );
  else
    MY_NOTIFY_FAIL( "Usage: join channel [name]." );
}

status leave( string str )
{
  string channel;

  if (!stringp( str ))
    return 0;
  if (sscanf( str, "channel %s", channel ) &&
      sscanf( channel, "%s %s", str, str ) != 2)
    return DATABASE->leave_channel( channel );
  else
    MY_NOTIFY_FAIL( "Usage: leave channel [name]." );
}

status create_channel( string str )
{
  string channel, openp;

  if (!stringp( str ))
    return 0;
  if (sscanf( str, "%s channel %s", openp, channel ) == 2 &&
      sscanf( channel, "%s %s", str, str ) != 2 &&
      (openp == "open" || openp == "closed"))
    return DATABASE->add_channel( channel, openp == "open" );
  else
    MY_NOTIFY_FAIL( "Usage: create [open/close] channel [name]." );
}

status add( string str )
{
  string user, channel;
  
  if (!stringp( str ))
    return 0;
  if (sscanf( str, "%s to %s", user, channel ) == 2 &&
      sscanf( user, "%s %s", str, str ) != 2 &&
      sscanf( channel, "%s %s", str, str ) != 2)
    return DATABASE->add_user( user, channel );
  else
    MY_NOTIFY_FAIL( "Usage: add [who] to [channel]." );
}

status remove( string str )
{
  string user, channel;
  
  if (!stringp( str ))
    return 0;
  if (sscanf( str, "%s from %s", user, channel ) == 2 &&
      sscanf( user, "%s %s", str, str ) != 2 &&
      sscanf( channel, "%s %s", str, str ) != 2)
    return DATABASE->remove_user( user, channel );
  else
    MY_NOTIFY_FAIL( "Usage: remove [who] from [channel]." );
}

string query_auto_load()
{
  return MASTER;
}

public int remove_object()
{
  DATABASE->remove_me();
  ::remove_object();
}
