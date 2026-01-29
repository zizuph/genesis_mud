#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
	set_short("Hall");
   set_long("The great hall ends here, and extends southeast "
	+"towards a bedroom, and northeast towards the mess "
	+"hall.  The flames from the torches mounted on the "
	+"walls jumps and flickers in a barely perceptible "
	+"breeze.  From moment to moment, the lighting "
	+"changes in here, so that shadows appear and fade "
	+"in turn.\n");
   add_item(({"torches","torch"}),"They are mounted on the "
	+"walls in bone sconces.\n");
   add_item(({"flame","flames"}),"They are jumping and "
	+"leaping in the slight breeze.\n");

	INSIDE;

	add_exit(WWORK+"hall2.c", "west", 0, 0);
	add_exit(WWORK+"mess.c", "northeast", 0, 0);
	add_exit(WWORK+"bedroom.c", "southeast", 0, 0);
}
