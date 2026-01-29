/* Created by Dajala   20.10.94
 * Here the shop used to be located.
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/gnome/local.h"
#include <macros.h>

inherit "/d/Krynn/std/room";

void
create_room()
{
	set_short("Empty cave");

	set_long("This cave seems deserted. A thin layer of dust has already "
		+ "settled on floor and walls. Footsteps, clearly visible "
		+ "near the entrance prove that there are occasional visitors "
		+ "though. An exit to the west has been blocked by a brick "
		+ "wall. There is a sign on the north wall.\n");

	add_exit(TDIR + "living2", "east", 0);

	INSIDE
	LIGHT

	add_item("sign","You can read it.\n");
	add_cmd_item("sign", "read", "The sign reads: The PlaceWherePeopleCome"
		+ "ToBuyAndSellThingsAtMutuallyAgreedUponPrices has moved to the "
		+ "third floor.\n");
	add_item("footsteps", "Behind yourself you see a line of footsteps following "
		+ "you.\n");
}
