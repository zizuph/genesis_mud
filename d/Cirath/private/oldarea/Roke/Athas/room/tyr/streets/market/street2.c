inherit "/std/room";
#include "road.h"

create_room() {

	set_short("On Market Street");
	set_long(BSS("You are walking on the Market Street in Tyr, "+
		"leading south from the town square, towards the "+
		"market. There is a small hut to the west here. "+
	"The market is to the south.\n"));

	add_item(({"hut","small hut"}),BSS(
			"The hut looks small and filthy, you cannot "+
			"imagine this hut giving much shelter during "+
			"the sand storms.\n"));

	add_exit(MAR_STR+"street1","north",0);
	add_exit(SLUM_D+"hut4","west",0);
	add_exit(SQUA_D+"mark2","south",0);

}
