inherit "/std/room";

#include "road.h"


create_room()	{

	set_short("Shield street");
	set_long(BSS("You are now at the north end of Shield "+
		"street, and directly to the west you see Rivens second hand "+
		"armoury. To the north you see the Main Gate Road, and you "+
		"can follow the Shield street farther south.\n"));

	add_exit(SHI_STR+"road2","south",0);
	add_exit(SHOP_D+"armours","west",0);
	add_exit(MGR_STR+"road2","north",0);

}
