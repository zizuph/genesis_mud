inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <macros.h>
 
 
reset_room()
{
 
 
}
 
create_room()
{
 
    set_short("Dark stairway");
    set_long("You are in a dark stairway leading down to something unknown.\n"+
	     "You can go up and down.\n");
 

 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(CELL_D+"hallway3","down",0);
	add_exit(CELL_D+"hallway2","up",0);



    add_item(({"stair", "stairs"}), BSS("They looks like they can crumble away any minute.\n"));
 
    call_out("reset_room", 1);
 
}
