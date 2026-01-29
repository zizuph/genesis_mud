/* Examples on doors, made by Nick */

inherit "/std/room";
#include "defs.h"

create_room() {
    object obj;
    object door;
    object door2;

    set_short("Granny's cottage");
     set_long("This is Granny's home.  You are in her kitchen, which is "+
		"filled with warmth and the smell of cinnamon and "+
              "homebaked goodies.  Light filters in from the open doors "+
              "and windows.\n");
	add_exit((FPATH+"cottage2"), "east", 0, 0);
	door = clone_object(FPATH + "granny_door.c");
    door->move(this_object());
}
