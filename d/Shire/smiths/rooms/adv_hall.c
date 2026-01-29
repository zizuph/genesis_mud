/*
 * Hallway that connects the back of the library to the 
 * advanced resting room
 * -- Finwe, November 2001
 */

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_room() {
   seteuid(getuid());

   set_short("Hallway");
   set_long("The hallway is plain looking and utilitarian in " +
        "design. It runs east towards the resting room and north " +
        "to the library. A carpet covers the floor.\n");

   add_item("carpet","It is a handwoven carpet made by humans.\n");

   add_prop(ROOM_I_INSIDE,1);
// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

   add_exit(SMITHSDIR_ROOMS + "library","north");
   add_exit(SMITHSDIR_ROOMS + "drop","east");
   

}

