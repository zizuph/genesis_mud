inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Sul street");
	set_long(BSS("You are standing on Sul street, just east of the "+
		"market place. There is a jewlery store north of here, and "+
		"a small hut south. You see a sign hanging over the "+
		"door to the jewlery store.\n"));

	add_item("sign","There is some writing on the sign, maybe you "+
		"could read it?\n");

	add_cmd_item("sign","read", BSS(
		"Olmhazan's Jewlery store.\n"));

	add_exit(SQUA_D+"mark2","west",0);
	add_exit(SHOP_D+"jewler","north","@@closed");
	add_exit(SLUM_D+"hut1","south",0);
	add_exit(SUL_STR+"road7","east",0);

}

closed()	{
	write(BSS("I, Olmhazan the jewler of Tyr, am sad to declare "+
		"that I will have to keep my shop closed for the next "+
		"few weeks due to burglary. Because of this, I have "+
		"made an agreement with Aurora, who owns the general "+
		"store, that she will accept gems and jewlery in the "+
		"near future.\n"));
	return 1;
}

