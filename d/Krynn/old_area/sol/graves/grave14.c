/* The graveyard
 *
 * Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

void
create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
	"You are in the Solace graveyard. Graves are all around you. " +
	"There is not much to be found here but graves. A small path " +
	"runs north and south. There is a rectangular hole here." +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE
    add_item("hole", "A coffin would fit nicely in that hole.\n");

    add_exit(TDIR + "grave9", "north");
    add_exit(TDIR + "grave19", "south");
    add_exit(TDIR + "hole0", "down");
}

int
query_grave_room() { return 14; }
