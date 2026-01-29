/* cliff_common.c, the baseroom for the cliffs */
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit "/std/room";

void create_cliff();
void create_room()
{

	set_long("   You are clinging to the side of the Black Cliffs. "+
		"From here you can climb either up or down, but neither "+
		"will be easy considering all the moisture and moss that "+
		"covers the sheer face of the cliff. The slightest wrong "+
		"move could send you plummeting to the jagged rocks "+
           "below. ");

	add_item(({"cliff", "cliffs", "Black Cliffs", "black cliffs"}), 
		"The cliff is black as night and perfectly vertical. "+
		"There are few places to grip it, but now that you are "+
		"on it, you have no choice but to climb up or down, "+
		"or fall... \n");
	add_item(({"moss", "moisture"}), "The wet moss on the surface of "+
		"the cliff makes it very difficult to climb.\n");
	add_item(({"rocks", "jagged rocks", "down"}), "You look down and "+
		"immediately regret it.  Far below you see the jagged "+
		"and broken rocks below.  To fall now would almost "+
		"certainly mean your death.\n");

	create_cliff();
}

create_cliff()
{
}
