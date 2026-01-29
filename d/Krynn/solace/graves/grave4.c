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
	"You are in the north east corner of the graveyard in Solace. The " +
	"graves here look less well kept than the graves further west. " +
	"Perhaps the old grave keeper thinks it's too far to come here." +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave3", "west", 0);
    add_exit(TDIR + "grave9", "south", 0);
}

query_grave_room() { return 4; }
