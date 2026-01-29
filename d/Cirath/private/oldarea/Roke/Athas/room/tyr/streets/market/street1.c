inherit "/std/room";
#include "road.h"

create_room() {

	set_short("Northern end of Market Street");
	set_long(BSS("You are walking on Market Street, leading south "+
		"from the town square in Tyr, towards the market. The "+
		"streets are dusty, and the buildings around here are "+
		"only huts.\n"));


	add_exit(SQUA_D+"square9","north",0);
	add_exit(SLUM_D+"hut5","east",0);
	add_exit(MAR_STR+"street2","south",0);

	add_item(({"hut","huts"}),BSS(
          "These huts look small and uncomfortable. It seems like "+
          "they don't offer much protection from the weather.\n"));

}
