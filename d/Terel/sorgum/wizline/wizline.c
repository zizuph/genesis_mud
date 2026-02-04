/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * wizline.c
 *
 * Multi-channel wizline object
 * Based on code written by windwalker
 *
 * Sorgum June 94
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "wizline.h"

/*
 * Global variables
 */

mapping wizline_help = 
(["wlhelp":"Usage: wlhelp [wizline-command]\n" +
           "Print help for wizline-command.  If wizline-command is not " +
           "given then print available commands.",
  "wllist":"Usage: wllist [open|closed]\n" +
           "List all open or closed channels you have access to.  Without " +
           "an argument, list both open and closed channels.  The channels " +
           "are displayed like: name (protection) <members> (owner).",
  "wlcreate":"Usage: wlcreate <open|closed> channel <name>\n" +
             "Create a new channel named <name>.  Anyone can join an open " +
             "channel, but to join a closed channel you must be added by " +
             "the owner.",
  "wldestruct":"Usage: wldestruct <name>\n" +
               "Destroy the channel name <name>.  Of course this will only " +
               "work if you are the owener of channel <name>.",
  "wljoin":"Usage: wljoin <name>\n" +
           "Join channel named <name>.  Anyone may join an open channel, " +
           "but to join a closed channel, the owner must execute a wladd " +
           "command on your behalf if you are not already on the user list.",
  "wlleave":"Usage: wlleave <name>\n" +
            "Leave the channel named <name>.",
  "wlhjoin":"Usage: wlhjoin <name>\n" +
            "Same as wljoin, but puts you on the hidden users list.",
  "wlhleave":"Usage: wlhleave <name>\n" +
            "Same as wlleave, but removes you from the hidden users list.",
  "wladd":"Usage: wladd <wizard> to <name>\n" +
          "Add the wizard named <wizard> to the closed channel named " +
          "<name>.  You must be the owner of channel <name>.",
  "wlremove":"Usage: wlremove <user> from <name>\n" +
             "Remove the wizard named <wizard> from the closed channel " +
             "named <name>.  You must be the owner of channel <name>.",
  "wlbusy":"Usage: wlbusy\n" +
           "Stop listening for messages over the channels.",
  "wlclear":"Usage: wlclear\n" +
            "Clear busy status previously set with wlbusy"
         
  ]);
			 
/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
public void
create_object()
{
    if (!IS_CLONE)
	return;
    seteuid(getuid());
    MANAGER->add_me();
    set_short("multi-channel wizline object");
    set_long("A multi-channel wizline object.  Use 'wlhelp' for help.\n");
    add_name("wizline");
    add_name("wizline-object");
    add_name("object");        
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    move(TP);
}

/*
 * Function name: remove_object
 * Description:   Removes this object from the game.
 */
public void
remove_object()
{
    MANAGER->remove_me();
    ::remove_object();
}

/*
 * Function name: query_auto_load
 * Description:   Make this object autoloading
 * Returns:       The filename of this object
 */
public string
query_auto_load()
{
    return MASTER;
}

/*
 * Function:    vanish
 * Description: Remove this object and print a message if it's in a room.
 */
nomask void
vanish()
{
    if (environment(TO)->query_prop(ROOM_I_IS))
	tell_room(environment(TO), "The wizline object vanishes.\n");
    remove_object();
}
    
/*
 * Function:    enter_env
 * Description: This function is called each time this object enters a
 *		new environment.  We use it to make sure that the object
 *              does not fall into the hands of a mortal.
 */
void enter_env(object dest, object old) 
{
    ::enter_env();
    if (!living(dest))
	return;
    if ("/secure/master"->query_wiz_level(dest->query_real_name()) == 0) {
	set_alarm(2.0, -1.0, "vanish");
    }
}
	
/*
 * Function:    leave_env
 * Description: This function is called each time this object leaves
 *		an environment.
 */
void leave_env(object old, object dest) 
{
    ::leave_env(old, dest);
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{

/*    if ((environment()) && (environment() == TP) &&
	(TP->query_wiz_level() == 0)) {
	TP->catch_msg("The wizline object suddenly disintegrates!\n");
	remove_object();
    }*/
    
    add_action("wlhelp", "wlhelp"); 
    add_action("wllist", "wllist");
    add_action("wlcreate", "wlcreate");
    add_action("wldestruct", "wldestruct");
    add_action("wldestruct", "wldestroy");        
    add_action("wljoin", "wljoin");
    add_action("wlleave", "wlleave");
    add_action("wlhjoin", "wlhjoin");
    add_action("wlhleave", "wlhleave");        
    add_action("wladd", "wladd");
    add_action("wlremove", "wlremove");
    add_action("send", "wiz", 1);
    add_action("wlbusy", "wlbusy");
    add_action("wlclear", "wlclear");    
    ::init();
}
	
/*
 * Function:    send
 * Description: Action to send a message.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
send(string str)
{
    return MANAGER->send(query_verb()[3..], str);
}
	
/*
 * Function:    send
 * Description: Action to send a message.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wlhelp(string str)
{
    if (!strlen(str)) {
	write("Wizline commands: \n\n" +
	       "\t wlhelp     -- wizline help command\n" +
	       "\t wllist     -- list channels\n" +
	       "\t wlcreate   -- create a channel\n" +
	       "\t wldestruct -- destruct a channel\n" +
	       "\t wljoin     -- join an existing channel\n" +		   
	       "\t wlleave    -- leave an existing channel\n" +
	       "\t wladd      -- add a wizard to a channel\n" +
	       "\t wlremove   -- remove a wizard from a channel\n" +
	       "\t wlbusy     -- stop listening to channels\n" +
	       "\t wlclear    -- clear busy status\n" +
	       "\t wiz<name>  -- send a message on channel\n\n" +
	       "Use wlhelp <command> for help on that command\n");
	return 1;	
    }
    
    if (!wizline_help[str]) {
	NF(str + " is not a vlaid wizline command.\n");
	return 0;
    }
    write(wizline_help[str] + "\n");
    return 1;
}
	
/*
 * Function:    wlcreate
 * Description: Action to create a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wlcreate(string str)
{
    string channel, protstr;
    int mode;

    NF("Usage: wlcreate <open|closed> channel <name>\n");

    if(!strlen(str))
	return 0;
    
    if ((sscanf(str, "%s channel %s", protstr, channel) == 2) &&
	(sscanf(channel, "%s %s", str, str) != 2)) {
	switch (protstr) {
	case "open":
	    mode = PROT_OPEN;
	    break;
	case "closed":
	    mode = PROT_CLOSED;
	    break;
	default:
	    return 0;
	    break;
	    }
	return MANAGER->create_channel(channel, mode);

    }
    return 0;
}
	
/*
 * Function:    wllist
 * Description: Action to list channels.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wllist(string str)
{
    int mode = 1;
    
    NF("Usage: wllist [open|closed]\n");

    switch (str) {
    case "open":
	mode = 1;
	break;
    case "closed":
	mode = 2;
	break;
    default:
	if (strlen(str))
	    return 0;
	else 
	    mode = 0;
	break;
    }
    return MANAGER->list_channels(mode);
}
	
/*
 * Function:    wldestruct
 * Description: Action to destruct a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wldestruct(string str)
{
    NF("Usage: wldestruct <name>\n");
    if (!strlen(str))
	return 0;
    return MANAGER->destroy_channel(str);
}
	
/*
 * Function:    wljoin
 * Description: Action to join a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wljoin(string str)
{
    NF("Usage: wljoin <name>\n");
    if (!strlen(str))
	return 0;
    return MANAGER->join_channel(str);
}
	
/*
 * Function:    wlleave
 * Description: Action to leave a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wlleave(string str)
{
    NF("Usage wlleave <name>\n");
    if (!strlen(str))
	return 0;
    return MANAGER->leave_channel(str);
}
	
/*
 * Function:    wljoin
 * Description: Action to join a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wlhjoin(string str)
{
    NF("Usage: wlhjoin <name>\n");
    if (!strlen(str))
	return 0;
    return MANAGER->join_channel_hidden(str);
}
	
/*
 * Function:    wlleave
 * Description: Action to leave a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wlhleave(string str)
{
    NF("Usage wlhleave <name>\n");
    if (!strlen(str))
	return 0;
    return MANAGER->leave_channel_hidden(str);
}

/*
 * Function:    wladd
 * Description: Action to add a user to a channel
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wladd(string str)
{
    string who, name;
    
    NF("Usage: wladd <wizard> to <name>\n");
    if (sscanf(str, "%s to %s", who, name) != 2)
	return 0;
    return MANAGER->modify_user_list(who, name, "add");
}

/*
 * Function:    wlremove
 * Description: Action to remove a user from a channel.
 * Arguments:   str - the message to send.
 * Retuens:     1/0
 */
public int
wlremove(string str)
{
    string who, name;
    NF("Usage: wladd <wizard> from <name>\n");
    if (sscanf(str, "%s from %s", who, name) != 2)
	return 0;
    return MANAGER->modify_user_list(who, name, "remove");
}
	
/*
 * Function:    wlbusy
 * Description: Action to gostop listening for messages
 * Arguments:   str - ignored
 * Retuens:     1/0
 */
public int
wlbusy(string str)
{
    TP->add_prop(WIZLINE_BUSY_PROP, 1);
    TP->catch_msg("You went busy on the wizline channels.\n");
    return 1;
}

/*
 * Function:    wlclear
 * Description: Action to clear busy status
 * Arguments:   str - ignored
 * Retuens:     1/0
 */
public int
wlclear(string str)
{
    TP->add_prop(WIZLINE_BUSY_PROP, 0);
    TP->catch_msg("You cleared busy status on the wizline channels.\n");
    return 1;
}
