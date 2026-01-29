inherit "/std/room";
#include "/d/Roke/common/defs.h"
 
 
reset_room()
{
 
 
}
 
create_room()
{
    object door;

    set_short("Hallway");
	set_long("");

    add_prop(ROOM_I_INSIDE, 1);

	add_exit(CELL_D+"celstair1","up",0);
	add_exit(CELL_D+"celstair2","down",0);

	add_item(({"wall","walls"}),BSS(
		"The walls are clammy due to the water streams flowing down. "+
		"There is cracks in the walls around here, and the water seems "+
		"to come from outside the walls.\n"));

	add_item(({"crack","cracks"}),BSS(
		"These cracks in the wall have small streams of water pouring "+
		"out of them.\n"));

	add_item(({"water"}),BSS(
		"The water is dirty, and it flows in small streams down the "+
		"wall. You wonder where so much water can come from in such "+
		"desert area that you are in now, and you start to suspect "+
		"Pandora for using her powers to water her garden too.\n"));

    call_out("reset_room", 1);

	door = clone_object(DOOR_D+"secr_door_c");
    door->move(this_object());
}
