/*  part of the track leading up to the volcano in the land of the dinosaurs.
    At the bottom of the volcano.

 
    coder(s):   Deinonychus
 
    history:	DD.MM.YY	what done			who did
		27.02.93	created				Deinonychus
 
    purpose:	none
    exits:	none
 
    objects:	none
    npcs:	none
 
    quests:	none
    special:	none
 
    to do:	none
    bug:	none known
*/
 
 
inherit "/std/room";
#include "track.h"
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_room()
 * Description	: Create the room.
 * Arguments:	  none
 * Returns:	  nothing
 */

void create_room()
{
    set_short("Bottom of volcano.");
    
    set_long(BS(
    "You're at the bottom of the volcano. South of you the mountains rise " +
    "high up to the sky. Northeast there's a quite high rockwall. It " +
    "seems to be impossible to climb it. Where the wall ends you can make " +
    "out a forest. The track to the west seems to lead up to the top of " +
    "the volcano.\n"));

#include "track.itm"
#include "south.itm"
       
    add_item(({"wall","rockwall"}), BS(
    "This wall really looks hard to climb. It is almost overhung and you " +
    "can't see any rifts or ledges you could use to climb up.\n"));
    
    add_item("forest",BS(
    "You can't see much of the forest down here. Maybe you can take a " +
    "closer look when you're a little higher on the volcano.\n"));

    add_item("hole",BS(
    "Well, what you see is a hole in the volcano. It's placed that high " +
    "that you can't reach it. So there's no way to climb into the hole. " +
    "Maybe it's better like that, because there's some blood on the edge " +
    "of it.\n"));

    add_exit(ROOM("linkroom"), "south", "@@block");
    add_exit(ROOM("track_01"), "west", 0);
}

/*****************************************************************************/

/*
 * Function name: block
 * Description:   blocks the player from going south
 * Arguments:	  none
 * Returns:	  1
 */

int block()
{
    write("I'm afraid this area isn't opened yet.\n");
    return 1;
}

/*****************************************************************************/

/*
 * Function name: init
 * Description:   adds some commands to the player
 * Arguments:	  none
 * Returns:	  nothing
 */

void
init()
{
    ::init();
    add_action("do_enter","enter");
    add_action("do_climb","climb");
}

/*****************************************************************************/

/*
 * Function name: do_enter
 * Description:   blocks players to enter the hole
 * Arguments:	  none
 * Returns:	  1/0
 */

int 
do_enter(string what)
{
    if (what == "hole"){
	NF(BS("Nobody has ever entered this hole here and you surely " +
	    "won't be the first to enter it.\n"));
	return 0;
    }
    else{
	NF("Enter what?");
	return 0;
    }
}

/*****************************************************************************/

/*
 * Function name: do_climb
 * Description:   blocks the player from climbing the wall
 * Arguments:	  none
 * Returns:	  nothing
 */

int 
do_climb(string what)
{
    if (what == "wall" || what == "rockwall"){
	NF(BS("You really think you can climb this wall? To be honest " +
	    "nobody has ever climbed it. In fact it really IS " +
	    "impossible to climb it, so let it be.\n"));
	return 0;
    }
    else{
	NF("Climb what?");
	return 0;
    }
}

