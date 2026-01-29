inherit "/std/room";
#include "square.h"

#define COM_STR "/d/Roke/Athas"

reset_room()
{
}
 
create_room()
{

	set_short("Southwest end of square");
	set_long(BS("You are at the southwest end of the town square "+
		"in Tyr, just east of the commons quarter. To your west "+
		"the Commoner Road makes its way through the houses, "+
		"and to your south the Merchant roads lies, making a "+
		"path in the slum-areas of Tyr. There is a slight layer "+
		"of sand lying over the square here.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square8","east",0);
	add_exit(COM_STR+"road1","west","@@closed");
	add_exit(SQUA_D+"square5","northeast",0);
	add_exit(SQUA_D+"square4","north",0);
	add_exit(MER_STR+"road1","south" );

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

closed()	{
	write(BSS("Due to building activities, the Commoners "+
		"road is closed. We hope we can have it opened "+
		"again very soon. Sorry for all inconvenience.\n"));
	return 1;
}

