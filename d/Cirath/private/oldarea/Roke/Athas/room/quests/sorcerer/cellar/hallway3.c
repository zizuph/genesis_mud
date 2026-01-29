inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
reset_room()
{
}
 
create_room()
{
    object door; 
    set_short("Hallway");
    set_long(BSS("You are in a dark hallway, there is a door east and a door west of "+
		"you, there is also some stairs leading down.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(CELL_D+"celstair3","down",0);
	add_exit(CELL_D+"celstair2","up",0);

    call_out("reset_room", 1);

	door = clone_object(DOOR_D+"wood_door_a");
    door->move(this_object());

	door = clone_object(DOOR_D+"iron_door_a");
    door->move(this_object());
    door->set_key(570157);
}
