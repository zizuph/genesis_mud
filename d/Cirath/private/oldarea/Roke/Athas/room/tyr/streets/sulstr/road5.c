inherit "/std/room";

#include "road.h"


create_room()	{
	set_short("Sul street");
	set_long(BSS("You are standing on Sul street, just west of the market. "+
		"The street continues on the other side of the market, "+
		"leading towards the Stadium Gate. There is a shop "+
		"directly north of here, and to the southwest "+
		"you see a tavern.\n"));

	add_exit(SUL_STR+"road4","west",0);
	add_exit(SHOP_D+"shop","north",0);
	add_exit(SQUA_D+"mark1","east",0);

}
