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
	"You are in the graveyard. There are many graves here, not all of " +
	"them are being used right now. Perhaps one is saved for you?" +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave0", "west");
    add_exit(TDIR + "grave2", "east");
}

query_grave_room() { return 1; }
