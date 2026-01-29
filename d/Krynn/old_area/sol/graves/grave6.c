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
	"You are standing in the graveyard of Solace. This is the graveyard " +
	"of all great heroes in Krynn. Some of these heroes are said to rest" +
	" light. Better keep your eyes open." +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave5", "west", 0);
    add_exit(TDIR + "grave7", "east", 0);
    add_exit(TDIR + "grave11", "south", 0);
}

query_grave_room() { return 6; }
