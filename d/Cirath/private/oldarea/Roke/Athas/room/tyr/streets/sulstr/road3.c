inherit "/std/room";

#include "road.h"


create_room()	{
	set_short("Sul street");
	set_long(BSS("You are walking along Sul street, which leads from "+
		"the Main Gate, through the market and to the "+
		"Stadium Gate. There is a tailor's to the west here, "+
		"and you can see some buildings to the northeast.\n"));

	add_exit(SUL_STR+"road2","northwest",0);
	add_exit(SHOP_D+"tailor","west","@@closed");
	add_exit(SUL_STR+"road4","southeast",0);

}

closed()	{
	write(BSS("The tailor is currently closed, please return "+
		"tomorrow.\n"));
	return 1;
}

