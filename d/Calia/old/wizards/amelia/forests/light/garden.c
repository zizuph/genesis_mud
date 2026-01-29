
inherit "/std/room";
#include "door.h"

#include "/sys/macros.h"
#include "defs.h"
create_room() {
    object door;

   set_short("Granny's garden");
   set_long("You find yourself in the middle of Granny's garden.\n");
	door = clone_object(FPATH+"garden_door_o");
	door->move(this_object());
}
