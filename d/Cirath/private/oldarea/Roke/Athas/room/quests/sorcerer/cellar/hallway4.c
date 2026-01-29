inherit "/std/room";
#include "/d/Roke/common/defs.h"

reset_room()
{

}
 
create_room()
{
    object door;

    set_short("Hallway");
    set_long(BSS("You are in a dark, clammy hallway beneath Pandora's home, there "+
		"is a hallway going west of here, and a door south. You can also "+
		"go up the stairs.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(CELL_D+"cellhall1","west",0);
	add_exit(CELL_D+"celstair3","up",0);

	door = clone_object(DOOR_D+"stone_door_a");
    door->move(this_object());
    door->set_key(230686);

    call_out("reset_room", 1);
}
