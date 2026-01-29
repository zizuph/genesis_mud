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
	"You are in the north part of the graveyard in Solace. It's very " +
	"quiet here. Maybe too quiet..... " +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave1", "west", 0);
    add_exit(TDIR + "grave3", "east", 0);
}

query_grave_room() { return 2; }
