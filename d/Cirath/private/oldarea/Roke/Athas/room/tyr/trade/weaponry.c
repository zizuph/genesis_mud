inherit "/std/room";

#include "trade.h"

create_room()	{

	set_short("Weaponrys storeroom");
	set_long("Store room for weaponrys.\n");

	add_exit(SHOP_D+"weapons", "east",0);

}
