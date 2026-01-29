#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit SHIRE_ROOM;
//  We want to make forest rooms herb searchable.
inherit HERB_SEARCH;

/*  You use create_forest_room to create your rooms.  It is the
 *  last thing called from the create_shire_room() and anything
 *  you put within the function will be what's added to the room.
 */
void
create_forest_room()
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
    add_item(({"tree","trees"}),"There are trees everywhere.\n");
    add_item("leaves","The trees are covered with leaves.\n");

    set_noshow_obvious(1);
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room  
    create_forest_room();
    // This function adds herbs to all the rooms which this file inherits
    // If you have added herbs yourself It will not add anymore
    add_std_herbs("forest");
}


//  We want to allow players to try and climb trees everywhere
//  in this forest.
void
init()
{
    ::init();  // _ALWAYS_ do this when you mask a function in a room
    add_action("do_climb","climb");
}

//  The climbing function
int
do_climb(string str)
{
    if (str != "tree")  
    {
	NF("Climb what?  The tree?\n");
	return 0;
    }
    write("You can't seem to get ahold of a branch in order to climb it.\n");
    return 1;
}
