/* 
 * Dock Road
 *
 * This road leads to the Newbie Line Dock
 *    Gelan - Sparkle - Port Macdunn - Grey Havens
 *
 * Created by Petros, April 2009
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "road.h"

inherit "/std/room";

void
create_room()
{
	set_short("On the docks of Gelan");
	set_long("The docks are crowded now, as usual.  The noise and "+
		"colour are truly impressive.  Mingling with the sounds "+
		"of the crowd are the cries of seagulls, flying "+
		"around and occasionally landing on the water.  "+
		"You see crates and sacks stacked on the wharf, "+
		"awaiting shipment. To the north you see a pier " +
		"where a ship can dock.\n");

	add_item((({"crates", "sacks"})),
		("The piles of goods are tightly sealed so no one "+
		"can open them.\n"));
	add_item("seagulls", "The seagulls are as noisy as "+
		"the people, as they hunt for fish in the sea.\n");
	add_item((({"crowd", "colour"})),
		("There is a crowd of people moving about here, "+
		"all different races, wearing all kinds of "+
		"colourful clothing.  They are fairly noisy.\n"));

    add_exit(ROAD + "dock1", "east", 0, 0);
    add_exit(ROAD + "dock3", "west", 0, 0);
    add_exit(GSL_SHIP_DIR + "newbie/pier2", "north", 0, 0);

	reset_room();
}
