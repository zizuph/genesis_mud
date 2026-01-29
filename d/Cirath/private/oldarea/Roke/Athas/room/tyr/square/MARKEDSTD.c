inherit "/std/room";

#include "square.h"

create_room()	{
	set_long(BSS("You are standing on the market place of Tyr, "+
		"south in the slum areas of the town. Further north "+
		"you will find the town square.\n"));

	create_market();

}

create_market()	{
}

