inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Middle of square");
	set_long(BS("You are at the middle of the town square of Tyr, "+
		"just west of the temple. There is a thin layer of sand  "+
		"on the marble square. To the north you can see towards "+
		"the nicer parts of Tyr, and farther south you see some "+
		"huts and houses owned by the poor inhabitants of "+
		"Tyr.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square4","west",0);
	add_exit(SQUA_D+"square6","east",0);
	add_exit(SQUA_D+"square7","southwest",0);
	add_exit(SQUA_D+"square3","northeast",0);
	add_exit(SQUA_D+"square9","southeast",0);
	add_exit(SQUA_D+"square1","northwest" );
	add_exit(SQUA_D+"square2","north",0);
	add_exit(SQUA_D+"square8","south",0);

	add_item(({"temple","temple"}),BSS(
			"You see a large and impressive temple, and you "+
			"recognize it as the well known 'Temple of Tyr'. "+
			"Maybe you should go closer ?\n"));
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
