/*
 * DOOR_A.c
 * 
 * Re-described and updated this door - Alaron July 26, 1996
 */

inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void
create_door()
{
    set_door_id("gravestone");
    set_pass_command(({"d","down"}));
    set_door_name(({ "gravestone", "tombstone", "stone", "tomb" }));
     set_open_desc("There is a large gravestone here. It is pushed "+
                   "aside a little, allowing entry into a hole "+
                   "leading down.\n");

    set_closed_desc("There is a large gravestone here.\n");

    set_door_desc( "There is an inscription saying 'Plugh the Warlock "+
		  "is resting here' on it.  On one side of the gravestone, "+
		  "someone has hung a note.\n");

    set_open_command("push");
    set_close_command("pull");

    set_open_mess( ({ "moves the gravestone, revealing an opening.\n",
		      "The stone above you moves to the side!\n" }) );
    set_close_mess( ({ "moves the gravestone, covering an opening.\n",
		       "The stone moves, blocking the exit!\n" }) );

    set_other_room(GRAVEYARD_DIR + "ingrave");
    set_open(0);
}
