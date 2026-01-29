inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Southern part of square");
	set_long(BS("You are on the southern part of the town square in "+
		"Tyr, just away from the temple. There is a thin layer of sand "+
		"around here. Directly south of you, you can see the north wall "+
		"of one of the small huts.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square7","west", );
	add_exit(SQUA_D+"square9","east", );
	add_exit(SQUA_D+"square4","northwest", );
	add_exit(SQUA_D+"square5","north", );
	add_exit(SQUA_D+"square6","northeast", );

	add_item(({"square","town square"}),BSS(
				"This square seems to be made of fine "+
				"layed marble rocks. There is a thin layer "+
				"of sand here, but the wind blows away "+
				"all tracks.\n"));
	add_item(({"sand","desert sand"}),BSS(
				"This is usual desert sand that has "+
				"blown in over the city walls. What did "+
				"you expect ?\n"));

	add_item(({"hut","huts"}), BSS(
			"The huts look like they should crumble "+
			"into pieces any second.\n"));
}
