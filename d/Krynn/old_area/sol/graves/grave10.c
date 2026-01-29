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
	"All is calm and quiet here, almost like if something was luring " +
	"on you. You feel like someone is watching you." +
	"", 70));


    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave11", "east", 0);
    add_exit(TDIR + "grave15", "south", 0);
}

query_grave_room() { return 10; }
