/* 	the Calian sanctuary in the crystalline palace second floor

    coder(s):   Glykron
    history:
		 1.21.95    moved to east of rack room	    Glykron
                 2. 1.95    exit added to recruiter room    Malcontent
                15.11.94    anti-bug code put in enver_inv  Maniac
		10.17.94    move start location to here     Glykron
                21. 9.94    check to filter out occ-guild 
                            people from doing quest         Maniac
                 1. 5.92    quest added                     Glykron
                 5. 4.92    created	                    Glykron
*/

#pragma save_binary

inherit "/std/room";
inherit "/lib/guild_support";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include RANDOM_HEADER
#include CALIAN_HEADER

void
create_room()
{
    set_short("Calian Sanctuary");
    set_long(
	"This is a trapezoidal room whose west and north walls slant away " +
	"from you to the southeast.  " +
	"There are several comfortable looking couches on which " +
	"you can <meditate> and redefine your personal priorities.  " +
	"\n");
    add_item( ({ "couch", "couches" }),
	"There are puffy looking couches of every color here.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_rack"), "west", 0, 0);
}

/*
 * Function name: gs_hook_start_meditate
 * Description:   Called when player starts to meditate
 */
void
gs_hook_start_meditate()
{
    write("" +
	"You sit down on a couch and slowly close your eyes.\n" +
	"A feeling of great ease and self control falls upon you.\n" +
	"You block of your senses and concentrate solely upon your\n" +
	"own mind. You find yourself able to <estimate> your different\n" +
	"preferences and <set> them at you own desire.\n" +
	"Just <rise> when you are done meditating.\n");
    say(QCTNAME(this_player()) + " sits down on a couch and starts " +
	"to meditate.\n");
}

/*
 * Function name: gs_hook_rise
 * Description:   Called when player rises from the meditation
 */
void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface of\n" +
	  "your consciousness. You exhale and feel very relaxed as you\n" +
	  "stand up.\n");
    say(QCTNAME(this_player()) + " comes out of a trance and stands up.\n");
}


void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate", "sit");
}