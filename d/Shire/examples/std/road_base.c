/*        road_base.c
 *
 *  This is a base inheritable file for the roads outside and around
 *  the town.  You add everything in which you want to have common
 *  to every room that this file is inherited by.
 */

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit SHIRE_ROOM;

/*  You use create_road_room to create your rooms.  It is the
 *  last thing called from the create_shire_room() and anything
 *  you put within the function will be what's added to the room.
 */
void
create_road_room()
{

}

/* The function create_shire_room creates a room with all the shire
 * room functionality.. no need to create a room using create_room
 * when you inherit /d/Shire/std/room.c in fact you should never
 * use create_room with the Shire/std/room.
 */
public void
create_shire_room()
{
    //  Put in whatever you wish to be in _every_ room that this file inherits
    add_item("road","The road is made of a peculiar colour of bricks.\n");
    add_item("bricks","The bricks are of a yellow colour, making this "+
      "the yellow brick road.\n");
    add_item(({"rocks","rock"}),"There are rocks laying all over the road.\n");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room  
    create_road_room();
}

//  We want to add our own kick emote to the road rooms 
void
init()
{
    ::init(); // Always make sure to do this when you mask a function
    add_action("do_kick","kick");
}

//  Now our kick emote
int
do_kick(string str)
{
    // when we "kick rock" or just type "kick" we do the emote 
    // otherwise we do the defualt kick. 
    if (str == "rock" || !str)
    {
	TP->catch_msg("You kick a rock down the road.\n");
	say(QCTNAME(TP)+" kicks a rock down the road.\n");
	return 1;
    }
    return 0;
}
