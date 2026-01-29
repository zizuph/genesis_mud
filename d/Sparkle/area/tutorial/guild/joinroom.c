/*
 *  /d/Sparkle/area/tutorial/guild/joinroom.c
 *
 *  Here we have a simple guild, the Patrol Guild of Silverdell. This is
 *  just something I copied and modified from the basic stuff located in:
 *
 *  /d/Genesis/doc/examples/guild/occ_fighter/
 *
 *  It is used to teach players the usefulness of joining guilds.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>
#include "guild.h"

#define TUTORIAL_CHAPTER  47  /* the chapter for the sign */


/* Prototypes */
public void       create_silverdell();
int               occjoin(string str);
int               occleave(string str);
void              init();
public int        check_exit();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("Inside the entrance hall of the Patrol Guild");

    set_long("You find yourself in a well-kept entrance hall for the"
      + " Patrol Guild of Silverdell. It is here that people who wish"
      + " to lend their talents to protecting these lands may <guildjoin>"
      + " to become a member. If already a member, it is possible to hang"
      + " up your horn and leave the guild with the command <guildleave>."
      + " Corridors extend to the east and south,"
      + " and the doorway leads back out to the northwest.\n\n");

    add_item( ({ "guild", "here", "room", "hall", "patrol guild",
                 "patrol guild of silverdell", "entrance", "entrance hall" }),
        "This guild is clearly a place where much is possible. You should"
      + " find this a useful and profitable home from which to begin your"
      + " daily adventures.\n");
    add_item( ({ "home" }),
        "Yes, this is a fine home for any adventurer.\n");
    add_item( ({ "adventurer" }),
        "That would be you, no?\n");
    add_item( ({ "corridor", "corridors" }),
        "They extend to the east and south.\n");
    add_item( ({ "east", "bunkroom" }),
        "The bunkroom lies east of here.\n");
    add_item( ({ "south", "training hall" }),
        "The training hall lies south of here.\n");
    add_item( ({ "door", "doorway", "northwest", "outside" }),
        "The door leads to the outside, heading northwest.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor here is quite clean - immaculately swept, in fact.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling is fairly high above you here in the hall.\n");
    add_item( ({ "sky" }),
        "The sky is not visible, here indoors.\n");

    add_exit(FARM_DIR + "crossroad_3", "northwest");
    add_exit("start", "east", check_exit, 1, 0);
    add_exit("train", "south", check_exit, 1, 0);

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

int
occjoin(string str)
{
    object sh;
    mixed why;

    if (strlen(str))
    {
        return 0;
    }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
	switch (sh->add_occ_shadow(this_player()))
	{
	    case 1:
	        /* We have successfully shadowed the player, so we're set */
		write("A chime sounds, and a few officers enter. They hand"
                  + " you a silver-plated horn, welcome you to the guild,"
                  + " and then return to their duties.\n\nYou are now a"
                  + " member of the Patrol of Silverdell. Welcome!\n\n");
		return 1;
    
	    case -4:
	        /* The player has an occ guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
		write("Your other guilds don't want you in this one!\n");
		break;
    
	    default:
	        /* Some error in shadowing */
		write("An error has prevented you from joining.\n");
		break;
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
occleave(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("But you aren't a member of this guild!\n");
        return 1;
    }

    this_player()->remove_occ_member();
    write("With mild regret, you turn in your silver-plated horn and"
      + " unregister your membership with the guild. You are now a free"
      + " agent, and ready to take on new frontiers.\n\nYou are no longer"
      + " a member of the Patrol of Silverdell!\n\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(occjoin, "guildjoin");
    add_action(occleave, "guildleave");

}


/*
 * Function name:        check_exit
 * Description  :        Allow players who are guild members to pass, and block
 *                       others.
 * Returns      :        int 1 - block, 0 - allow passage
 */
public int
check_exit()
{
    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        if (this_player()->query_wiz_level())
        {
            write("You may pass, noble wizard.\n");
        }
        else
        {
            write("Only members of the guild may proceed further. If you wish,"
              + " you may <guildjoin> to become a member yourself.\n");
            return 1;
        }
    }

    return 0;
} /* check_exit */


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */
