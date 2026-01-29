

/* room2.c
   Mort 911004 */

inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {
	object ob;

    set_short("Great Chasm");
    set_long("This is the north end of a great chasm, that spreads\n" +
             "out to the east. It seems impossible to climb down, making\n" +
	     "travel only possible to the west.\n");
    add_exit("/d/Terel/mountains/ice5", "west",0);
    ob = clone_object(CEDRICDIR+"thane/grave.c");
     ob->move(this_object());
}

/*
 * Function name:
 * Description  :
 */

