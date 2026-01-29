/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The store room");
        set_long(BS(
           "You find yourself in an old deserted store room. Bags of flour"
	 + " lie strewn about the room, and everything is absolutely covered"
	 + " in the fine white powder. An old sewer pipe leads up out"
	 + " of the room.", 70));

	add_exit(CDIR + "northtmpl.c", "up", "@@up");
	add_exit(DDIR + "highstreet1.c", "east", 0);

	add_item(({"pipe", "sewer pipe", "floor"}), "@@pipe");
	add_item(({"flour", "bags", "powder", "white powder"}), "@@flour");
	INSIDE
        DARK
}

pipe()
{
	write("The cataclysm seems to have forced the old sewer pipe up"
	 + " through the one of the walls.\n");
	return "";
}

up()
{
	write("The pipe is too slippery to climb.\n");
	return 1;
}

flour()
{
	write("It looks just like ordinary flour to you.\n");
	return "";
}
