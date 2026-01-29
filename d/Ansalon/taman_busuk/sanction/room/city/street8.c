#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street before a bridge that crosses a river of lava");
    set_extra_long("Here you stand on the northern edge of a " +
      "teeming slum that has stopped expanding only because of the " +
      "extremely hot lava stream that runs past you to your north. " +
      "A stone bridge has been constructed here that crosses over " +
      "the river of molten rock. To your west stands a stone tower, " +
      "rising precariously on the edge of the lava flow.");

    add_item(({"hot lava stream","lava stream","river",
	"flow","lava flow",
	"river of molten rock","lava"}),
      "From the east a lava river runs past you to the west and " +
      "into the harbour. The heat from this river is staggering, " +
      "and you feel faint standing at this distance from it.\n");
    add_item(({"stone bridge","bridge"}),
      "A stone bridge crosses the river of lava to your north. " +
      "How it was constructed is anyones guess.\n");
    add_item(({"stone tower","tower"}),
      "This stone tower is of strange design, rising two stories to " +
      "a flat platformed roof. It stands on the very edge of " +
      "the lava flow, so how long it lasts standing there cannot " +
      "be any great time span.\n");

    add_exit(SCITY + "street21","north","@@cross_bridge");
    add_exit(SCITY + "tower_base","west","@@no_go");
    add_exit(SCITY + "street7","south",0);
    add_exit(SCITY + "street9","east",0);

    slum_descriptions();
}

int
cross_bridge()
{
/*
    write("As you start your way across the bridge, you " +
      "realise that it has been damaged (it looks like " +
      "a blind dragon has run into it), and is probably " +
      "a little dangerous to cross. You'd best come back " +
      "later when it is repaired.\n");
    return 1;
*/
    write("You step on to the stone bridge.\n");
    return 0;
}

int
no_go()
{
    if(TP->query_dragonarmy_occ_member())
	return 0;
    write("You knock on the door of the tower. A metal window slides " +
      "open and two beady eyes owned by a guard look out at you " +
      "with a scowl.\nThe guard says: You aren't from the " +
      "dragonarmies! Bugger off!\n");
    say(QCTNAME(TP)+ " knocks on the door of the tower to your " +
      "west. A metal window slides open and two beady eyes owned by a " +
      "guard look out at him.\nThe guard says: You aren't " +
      "from the dragonarmies! Bugger off!\n");
    return 1;
}
