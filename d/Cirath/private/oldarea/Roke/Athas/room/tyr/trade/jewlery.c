inherit "/std/room";

#include "trade.h"

create_room()	{

	set_short("Jewlery's store room");
	set_long("Store room for jewlery.\n");

	add_exit(SHOP_D+"jewler", "west",0);

}
