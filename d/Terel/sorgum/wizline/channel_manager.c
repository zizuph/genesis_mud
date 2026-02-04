/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * channel_manager.c
 *
 * Manage the wizline database.
 * Based on code written by Windwalker.
 *
 * Sorgum June 1994
 */

inherit "/std/object";

#include <macros.h>
#include "wizline.h"

#define REALNAME(x)  x->query_real_name()
#define IS_MEMBER(x, y) (member_array(x, channels[y][CHANNEL_USERS]) != -1)
#define IS_HMEMBER(x, y) (member_array(x, channels[y][CHANNEL_HUSERS]) != -1)
#define OWNER(chan) channels[chan][CHANNEL_OWNER]

/*
 * Global Variables
 */

static mapping users;
mapping channels;

/*
 * Function name: authorized
 * Description:   Test if a player is authorized to perform priveledged
 *                operations.
 * Arguments:     who - player object we want to test
 * Returns:       1 if authorized 0 otherwise
 */
nomask int
authorized(object who)
{
    if ((who->query_wiz_level() > 40) ||
	(member_array(who->query_real_name(), TRUSTED) != -1))
	return 1;
    else
	return 0;
}
			 
/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
public void
create_object()
{
    if (IS_CLONE) {
	"/secure/master"->do_debug("destroy", TO);
	throw("The channel_manager may not be cloned.");
    }
    channels = ([ ]);
    users = ([ ]);
    seteuid(getuid());
    restore_object(DATABASE);
}
			 
/*
 * Function name: add_me
 * Description:   Add this player to the user mapping.  This gets called
 *                from wizline::create_object()
 */
public void
add_me()
{
    users[TP->query_real_name()] = TP; 
}

/*
 * Function name: remove_me
 * Description:   Remove this player to the user mapping.  This gets called
 *                from wizline::remove_object()
 */
remove_me()
{
    users = m_delete(users, REALNAME(TP));
}

/*
 * Function name: query_users
 * Description:   This routine was created for bebugging purposes, but
 *                was left in because it may continue to be useful.
 * Returns:       The users mapping.
 */
public mapping
query_users()
{
    return users;
}

/*
 * Function name: query_channels
 * Description:   This routine was created for bebugging purposes, but
 *                was left in because it may continue to be useful.
 * Returns:       The channels mapping if this user is authorized, 0
 *                otherwise.
 */
nomask mixed
query_channels()
{
    if (authorized(TP))
	return channels;
    else
	return 0;
}
			 
/*
 * Function name: create_channel
 * Description:   Create a new channel
 * Arguments:     name - name of the new channel
 *                prot - protection mode (open or closed)
 * Returns:       1 if successful, 0 otherwise
 */
int
create_channel(string name, int prot)
{
    string lname, playername, protstr;
    
    lname = lower_case(name);
    if (channels[lname]) {
	NF("There is already a channel named " + name + ".\n");
	return 0;
    }

    if (member_array(capitalize(lname),
		     "/secure/master"->query_domain_list()) != -1) {
	NF("A channel may not have the same name as a domain.\n");
	return 0;
    }

    playername = REALNAME(TP);
    channels[lname] = ({name, ({playername}), ({ }), prot, playername});
    save_object(DATABASE);

    if (prot == PROT_OPEN)
	protstr = "open";
    else
	protstr = "closed";

    TP->catch_msg("Created " + protstr + " channel named " + name + "\n");
    return 1;
}
			 
/*
 * Function name: destroy_channel
 * Description:   Create a new channel
 * Arguments:     name - name of the channel
 * Returns:       1 if successful, 0 otherwise
 */
int
destroy_channel(string name)
{
    string lname;
    string player_name;

    lname = lower_case(name);
    if(!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    player_name = REALNAME(TP);
    if (!authorized(TP) && (player_name != OWNER(lname))) {
	NF("You are not authorized to destroy that channel.\n");
	return 0;
    }

    channels = m_delete(channels, lname);
    save_object(DATABASE);    
    TP->catch_msg("You just destroyed the " + name + " channel.\n");
    return 1;
}
			 
/*
 * Function name: format_channel
 * Description:   Return a string of the channel data in a format suitable
 *                for printing.
 * Arguments:     chan - A channel
 * Returns:       The formatted string that contains the channel data
 */
string
format_channel(mixed *chan)
{
    string user_list;
    string protstr;

    if (chan[CHANNEL_PROT] == PROT_OPEN)
	protstr = "open";
    else
	protstr = "closed";

    user_list = implode(chan[CHANNEL_USERS], ", ");

    if (authorized(TP)) {
	if (sizeof(chan[CHANNEL_HUSERS]))
	    user_list += " [" + implode(chan[CHANNEL_HUSERS], ", ") + "]";
    }
    
    return chan[CHANNEL_NAME] + " (" + protstr + ") <" + user_list + "> (" +
	chan[CHANNEL_OWNER] + ")\n";
}
			 
/*
 * Function name: list_channels
 * Description:   List channels
 * Arguments:     mode - display mode (0 = all, 1 = open 2 = closed)
 * Returns:       1 if successful, 0 otherwise
 */
int
list_channels(int mode)
{
    int i;
    string player_name;
    mixed *channel_data;
    mixed *chan;
    string msg;
    string protstr;
    int display;

    /*
     * modes:
     *         0 - print all channels
     *         1 - print just open channels
     *         2 - print just closed channels
     */
    
    msg = "";
    player_name = REALNAME(TP);

    channel_data = m_values(channels);
    for (i = 0; i < sizeof(channel_data); i++) {
	chan = channel_data[i];
	display = 0;
	switch (mode) {
	case 0:
	    if (authorized(TP) || (chan[CHANNEL_PROT] == PROT_OPEN) ||
		(member_array(player_name, chan[CHANNEL_USERS]) != -1)) 
		display = 1;
	    break;
	case 1:
	    if (chan[CHANNEL_PROT] == PROT_OPEN)
		display = 1;
	    break;
	case 2:
	    if ((chan[CHANNEL_PROT] == PROT_CLOSED) &&
		(authorized(TP) ||
		(member_array(player_name, chan[CHANNEL_USERS]) != -1)))
		display = 1;
	    break;
	default:
	    if (authorized(TP))
		display = 1;
	    break;
	}
	if (display)
	    msg += format_channel(chan);

    }

    if (!strlen(msg))
	msg = "There are no channels.\n";

    TP->catch_msg(msg);
    return 1;
}
			 
/*
 * Function name: join_channel
 * Description:   Join a channel
 * Arguments:     name - name of the channel
 * Returns:       1 if successful, 0 otherwise
 */
int
join_channel(string name)
{
    string lname;
    string player_name;

    lname = lower_case(name);
    if (!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    player_name = REALNAME(TP);
    
    if ((channels[lname][CHANNEL_PROT] == PROT_CLOSED) && !authorized(TP)) {
	NF("Sorry, that channel is closed.  You must be added by " +
	   capitalize(OWNER(lname)) + " before you may join.\n");
	return 0;
    }
    
    if (IS_MEMBER(player_name, lname)) {
	NF("You are already a member of channel " + name + "\n");
	return 0;
    }
    
    channels[lname][CHANNEL_USERS] += ({ player_name });
    save_object(DATABASE);    
    TP->catch_msg("You joined the " + name + " channel.\n");
    return 1;
}
			 
/*
 * Function name: join_channel_hidden
 * Description:   Join a channel's hidden members list
 * Arguments:     name - name of the channel
 * Returns:       1 if successful, 0 otherwise
 */
int
join_channel_hidden(string name)
{
    string lname;
    string player_name;

    if (!authorized(TP)) {
	NF("You are not authorized to do that.\n");
	return 0;
    }
    
    lname = lower_case(name);
    if (!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    player_name = REALNAME(TP);

    if (IS_MEMBER(player_name, lname)) {
	NF("You are on the normal users list.\n");
	return 0;
    }
    
    if (IS_HMEMBER(player_name, lname)) {
	NF("You are already a hidden member of channel " + name + "\n");
	return 0;
    }
    
    channels[lname][CHANNEL_HUSERS] += ({ player_name });
    save_object(DATABASE);    
    TP->catch_msg("You joined the " + name +" channel's hidden member list.\n");
    return 1;
}
		        
/*
 * Function name: leave_channel
 * Description:   Leave a channel
 * Arguments:     name - name of the channel
 * Returns:       1 if successful, 0 otherwise
 */
int
leave_channel(string name)
{
    string lname;
    string player_name;

    lname = lower_case(name);
    if (!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    player_name = REALNAME(TP);
    if (!IS_MEMBER(player_name, lname)) {
	NF("You were not a member of the channel " + name + " in the first " +
	   "place.\n");
	return 0;
    }

    if (player_name == OWNER(lname)) {
	NF("You can not leave a channel you own.  You could destroy it " +
	   "though.\n");
	return 0;
    }
    
    channels[lname][CHANNEL_USERS] -= ({ player_name });
    save_object(DATABASE);    
    TP->catch_msg("You left the " + name + " channel.\n");
    return 1;
}
		        
/*
 * Function name: leave_channel_hidden
 * Description:   Leave a channel
 * Arguments:     name - name of the channel
 * Returns:       1 if successful, 0 otherwise
 */
int
leave_channel_hidden(string name)
{
    string lname;
    string player_name;

    if (!authorized(TP)) {
	NF("You are not authorized to do that.\n");
	return 0;
    }
    
    lname = lower_case(name);
    if (!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    player_name = REALNAME(TP);
    if (!IS_HMEMBER(player_name, lname)) {
	NF("You were not a hidden member of the channel " + name +
	   " in the first place.\n");
	return 0;
    }

    if (player_name == OWNER(lname)) {
	NF("You can not leave a channel you own.  You could destroy it " +
	   "though.\n");
	return 0;
    }
    
    channels[lname][CHANNEL_HUSERS] -= ({ player_name });
    save_object(DATABASE);    
    TP->catch_msg("You left the " + name + " channel's hidden member list.\n");
    return 1;
}

/*
 * Function name: modify_user_list
 * Description:   Add or delete a wizard from the user list of a channel
 * Arguments:     who   - name of the wizard
 *                name  - name of the channel
 *                opstr - The desired operation ("add" or "remove")
 * Returns:       1 if successful, 0 otherwise
 */
int
modify_user_list(string who, string name, string opstr)
{
    string lname;
    string player_name;
    string ending;
    int is_member;

    lname = lower_case(name);
    if(!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    player_name = REALNAME(TP);
    if ((OWNER(lname) != player_name) && (!authorized(TP))) {
	NF("You are not authorized to " + opstr + " users on the " + name +
	   " channel.\n");
	return 0;
    }
    

    if (channels[lname][CHANNEL_PROT] == PROT_OPEN) {
	NF(name + " is an open channel.\n");
	return 0;
    }

    is_member = IS_MEMBER(lower_case(who), lname);
    
    if (opstr == "add") {
	if (is_member) {
	    NF(capitalize(who) + " is already a member of channel " +
	       name + "\n");
	    return 0;
	}
	else
	    channels[lname][CHANNEL_USERS] += ({ lower_case(who) });
	ending = "ed";
    }
    else {
	if (!is_member) {
	    NF(capitalize(who) + " was not on the user list in the first " +
	       "place.\n");
	    return 0;
	}
	else
	    channels[lname][CHANNEL_USERS] -= ({ lower_case(who) });
	ending = "d";
    }

    save_object(DATABASE);    
    TP->catch_msg("You " + opstr + ending + " " + capitalize(who) +
		  " on channel " + name +"\n");
    return 1;
}

/*
 * Function name: send
 * Description:   Send a message on a channel
 * Arguments:     name  - name of the channel
 *                msg   - The message
 * Returns:       1 if successful, 0 otherwise
 */
int
send(string name, string msg)
{
    string lname;
    string cname;
    string player_name;
    string *user_list;
    int i;

    lname = lower_case(name);
    cname = capitalize(name);
    player_name = REALNAME(TP);
    
    if (member_array(cname, "secure/master"->query_domain_list()) != -1) {
	NF("Domain messages are not currently supported.\n");
	return 0;
    }

    if (!channels[lname]) {
	NF("Channel " + name + " does not exist.\n");
	return 0;
    }

    if (!authorized(TP) && (!(IS_MEMBER(player_name, lname)))) {
	NF("You are not a member of channel " + name + "\n");
	return 0;
    }

    user_list = channels[lname][CHANNEL_USERS];
    user_list &= m_indexes(users);

    for (i = 0; i < sizeof(user_list); i++) {
	if (!users[ user_list[i] ])
	    users = m_delete(users, user_list[i]);
	else
	    if (users[ user_list[i] ]->query_prop(WIZLINE_BUSY_PROP) == 0)
	    tell_object(users[ user_list[i] ], channels[lname][CHANNEL_NAME] +
			" @ " + capitalize(player_name) + ": " + msg + "\n");
    }

    user_list = channels[lname][CHANNEL_HUSERS];
    user_list &= m_indexes(users);
    for (i = 0; i < sizeof(user_list); i++) {
	if (!users[ user_list[i] ])
	    users = m_delete(users, user_list[i]);
	else
	    if (users[ user_list[i] ]->query_prop(WIZLINE_BUSY_PROP) == 0)    
	    tell_object(users[ user_list[i] ], channels[lname][CHANNEL_NAME] +
			" ** " + capitalize(player_name) + ": " + msg + "\n");
    }
			     
    return 1;
}
	    
    
    
    
