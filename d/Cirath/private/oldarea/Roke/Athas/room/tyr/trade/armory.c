inherit "/std/room";

#include "trade.h"

create_room()	{

	set_short("Armourers storeroom");
	set_long("Store room for armourers.\n");

	add_exit(SHOP_D+"armours", "east",0);

}
