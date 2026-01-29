inherit "/std/room";

#include "trade.h"

create_room()	{

	set_short("Generalstore's store room");
	set_long("Store room for generalstore.\n");

	add_exit(SHOP_D+"shop", "east",0);

}
