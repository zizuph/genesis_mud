/* This is the main Grunts guild room. This room handles joining, leaving, */
/* and issues replacement collars. Originally coded by Tulix I.            */
/* Recoded 28/12/95 with various improvements, Tulix III.                  */


/* Blocked up exit and added portal to the Emerald piers ...
 * Done because of temporary domain closing.
 * Unblock exit and remove portal when domain re-opens.
 *             - Alaron September 12, 1996
 */


inherit "/lib/guild_support";
inherit "/std/room";

/* These two lines are put in to keep Mercade happy */
#pragma strict_types
#pragma save_binary  

#include <stdproperties.h>
#include <macros.h>

#include "default.h"
#include "../guild.h"
 
/* Prototype functions */
public int join(string str);
public int my_leave(string str);
public int start(string str);
public int list();

/*
 * Function name:   create_room
 * Description:     define all the basics of the room
 */
public void
create_room()
{
    set_short("Smelly Grunts guild room");
    set_long(
	"   What a disgusting smell! This cave has never been cleaned "
      + "since the day it was made. Just the right place for a Goblin "
      + "race guild: and thats exactly what this place is. "
      + "There is a library to the east if you wish to learn more about "
      + "the 'Grunts' guild, assuming you can read of course.\n\n"
      + "In this room you can join the guild <want to smell>, "
      + "furthermore, you can "
      + "leave the guild <hate the smell>, "
      + "and also list the guilds that you are a member of <list>. "
      + "If you are a member of the guild, you can start here if you "
      + "wish to <start here>.\n");

    add_prop(ROOM_I_INSIDE, 1);
    
    add_exit(CAVE_DIR + "levelb/cave10b", "up", 0, 1);
    add_exit("shop",             "down",  0, 1);
    add_exit("boardroom",        "west",  0, 1);
    add_exit("secret_passage4c", "south", 0, 1);
    add_exit("alcove",           "north", 0, 1);
 
    add_item(({"walls","wall"}),
	"The walls are cold, and damp to touch. It seems to be volcanic " +
	"rock that these caves are made of. Pretty hard stuff it is, too.\n");

    add_item(({"roof","ceiling"}),
	"What little you can see above you suggests that the roof is made " +
	"of the same rock as the walls, volcanic rock. At least you can " +
	"be fairly sure the roof won't be falling down, as volcanic rock " +
	"is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is made " +
	"of volcanic rock.\n");
}
 
/*
 * Function name:   init
 * Description:     add commands to all players who enter the room
 */
public void
init()
{
    ::init();
    add_action( join,     "want"  );
    add_action( my_leave, "hate"  );
    add_action( start,    "start" );
    add_action( list,     "list"  );
}

 
/*
 * Function name:   join
 * Description:     see if player is fit to join guild, and make them a member
 * Arguments:       str: string containing the rest of the 'join' command
 * Returns:         1 if command successful, 0 if not.
 */
public int
join(string str)
{
    mixed why;
    object shadow;
 
    /* Verify that the player used the correct command to join */
    if (str!="to smell")
    {
	NF("Want to what? Smell perhaps?\n");
	return 0;
    }

    /* Check to see if the player already belongs to a race guild */
    if (TP->query_guild_member(GUILD_TYPE))
    {
	write("Tsk! Tsk! No way you can join two race guilds.\n");
	return 1;
    }
    
    setuid();
    seteuid(getuid(this_player()));

    /* We should now be able to add the guild shadow successfully */
    shadow = clone_object(GUILD_SHADOW);

    if (stringp(why = shadow->acceptable_grunts_member(this_player())))
    {
        write(why);
        shadow->remove_shadow();
        return 1;
    }

    if (shadow->add_grunts_shadow(this_player()) != 1)
    {
	shadow->remove_shadow();
        write("Could not make you a member for some reason.\n");
	return 1;
    }

    write("Ok.\n");    
    return 1;
}
 
/*
 * Function name:   my_leave
 * Description:     remove player from the guild
 * Arguments:       str: string containing the rest of the 'leave' command
 * Returns:         1 if command successful, 0 if not.
 */
public int
my_leave(string str)
{
    /* Verify that the player used the correct command to leave */
    if (str!="the smell")
    {
	NF("What do you hate? The smell perhaps?\n");
	return 0;
    }
 
    /* Check to see if the player belongs to the Grunts guild */
    if (TP->query_guild_name_race() != GUILD_NAME)
    {
	NF("You can't leave a guild you are not a member of.\n");
	return 0;
    }
    
    this_player()->remove_grunts_member();
    write("Ok.\n");
    return 1;
}
 
/*
 * Function name:   list
 * Description:     list guilds that player is a memeber of
 * Returns:         1
 */
public int
list()
{
    string str;
 
    str = TP->list_major_guilds();
    if (str)
	write("You are a member of the following guilds.\n" + str);
    else
	write("You are not a member of any important guilds.\n");
 
    return 1;
}
 
/*
 * Function name:   start
 * Description:     change default start location to this room
 * Arguments:       str: string containing the rest of the 'start' command
 * Returns:         1 if command successful, 0 if not.
 */
public int
start(string str)
{
    /* Verify that the player used the correct command */
    if (str != "here")
    {
	NF("Start what? Do you mean start here, perhaps?\n");
	return 0;
    }
    
    /* Check to see if the player belongs to the Grunts guild */
    if (this_player()->query_guild_name_race()!=GUILD_NAME)
    {
	write("Nice try, but you have to join the guild first.\n");
	return 1;
    }
    
    this_player()->set_default_start_location(MASTER);
    write("In future you will start here.\n");
    return 1;
}
