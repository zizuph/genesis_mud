inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
 
reset_room()
{
 
 
}
 
create_room(){
    object door;


    set_short("Dark stairway");
	set_long(BSS("You are in a dark stairway, leading down "+
		"into the unknown cellar of the Templar Pandora's "+
		"house. You think you can hear sounds, but you are not "+
		"completely sure.\n"));
 

 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(CELL_D+"hallway2","down",0);



    add_item(({"stair", "stairs"}), BSS("They looks like they can crumble away any minute.\n"));

	door = clone_object(DOOR_D+"secr_door_b");
    door->move(this_object());

    call_out("reset_room", 1);
 
}
