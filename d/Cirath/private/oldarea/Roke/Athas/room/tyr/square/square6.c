inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Eastern part of square");
	set_long(BS("You are on the east end of the town square in "+
		"Tyr, just outside the temple. To your east you see the "+
		"entrance to the 'Temple of Tyr', a well known place "+
		"to the adventurers of Athas. There is a thin layer of "+
		"sand covering the marble square, and parts of the "+
		"temple.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square5","west",0);
	add_exit(TEMP_D+"entrance","east",0);
	add_exit(SQUA_D+"square8","southwest",0);
	add_exit(SQUA_D+"square2","northwest",0);
	add_exit(SQUA_D+"square9","south",0);
	add_exit(SQUA_D+"square3","north",0);

	add_item(({"temple","temple"}),BSS(
			"You see a large and impressive temple, and you "+
			"recognize it as the well known 'Temple of Tyr'. "+
			"Maybe you should go inside ?\n"));
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
