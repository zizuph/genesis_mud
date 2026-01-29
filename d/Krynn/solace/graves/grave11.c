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
	"Small paths run off here and there and disappear behind the graves. " +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_item("paths", "The run off east, west and north, all seem well used.\n");

    add_exit(TDIR + "grave6", "north", 0);
    add_exit(TDIR + "grave12", "east", 0);
    add_exit(TDIR + "grave10", "west", 0);
}

query_grave_room() { return 11; }
