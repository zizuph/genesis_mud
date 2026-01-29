inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Northern part of square");
	set_long(BS("You are on the northern part of the town square in "+
		"Tyr, just away from the temple. There is a thin layer of sand "+
		"around here. Directly north of you, you can see the south wall "+
		"of the nobles banquet hall.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square1","west" );
	add_exit(SQUA_D+"square3","east",0);
	add_exit(SQUA_D+"square4","southwest",0);
	add_exit(SQUA_D+"square5","south",0);
	add_exit(SQUA_D+"square6","southeast",0);

	add_item(({"square","town square"}),BSS(
				"This square seems to be made of fine "+
				"layed marble rocks. There is a thin layer "+
				"of sand here, but the wind blows away "+
				"all tracks.\n"));
	add_item(({"sand","desert sand"}),BSS(
				"This is usual desert sand that has "+
				"blown in over the city walls. What did "+
				"you expect ?\n"));


}
