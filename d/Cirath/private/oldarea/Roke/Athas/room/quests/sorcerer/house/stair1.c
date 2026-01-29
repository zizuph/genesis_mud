inherit "/std/room";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
 
create_room()
{
 
    set_short("Light stairway");
    set_long("You are climbing stairs in a light stairway, you can go \n"+
	     "up and down.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HOUS_D+"livingroom","down",0);
    add_exit(HOUS_D+"stair2","up",0);

    add_item(({"stair", "stairs"}), "Nice stonestairs that looks like they are\n"+
	       "carved out of one stone\n");
 
}
