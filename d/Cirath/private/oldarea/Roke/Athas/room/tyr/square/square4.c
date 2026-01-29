inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Western part of square");
	set_long(BS("You are on the west end of the town square in "+
		"Tyr, just outside the temple. Far to your east you see the "+
		"'Temple of Tyr', a well know place "+
		"to the adventurers of Athas. There is a thin layer of "+
		"sand covering the marble square, and parts of the "+
		"temple.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square5","east",0);
	add_exit(SQUA_D+"square8","southeast",0);
	add_exit(SQUA_D+"square2","northeast",0);
	add_exit(SQUA_D+"square7","south",0);
	add_exit(SQUA_D+"square1","north" );

	add_item(({"temple","temple of tyr"}),BSS(
				"The temple looks mighty impressive "+
				"from here, maybe you could try "+
				"getting closer ?\n"));
	add_item(({"square","town square"}),BSS(
				"This square seems to be made of fine "+
				"layed marble rocks. There is a thin layer "+
				"of sand here, but the winds blows away "+
				"all tracks.\n"));
	add_item(({"sand","desert sand"}),BSS(
				"This is usual desert sand that has "+
				"blown in over the city walls. What did "+
				"you expect ?\n"));

}
