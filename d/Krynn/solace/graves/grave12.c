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
	"There is not a sound to be heard anywhere, spooky." +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave13", "east", 0);
    add_exit(TDIR + "grave11", "west", 0);
    add_exit(TDIR + "grave17", "south", 0);
}

int
query_grave_room() { return 12; }
