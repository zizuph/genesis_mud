/* The graveyard
 *

 * Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
	"You are standing in a graveyard. The inhabitants in Solace like to " +
	"keep away from this graveyard. Some say it's haunted, but then agai" +
	"n, which graveyard isn't." +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave0", "north", 0);
    add_exit(TDIR + "grave6", "east", 0);
}

query_grave_room() { return 5; }
