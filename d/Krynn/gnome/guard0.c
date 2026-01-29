#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
#include <ss_types.h>

inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Main guard room");
    set_long(BS("This is the main guard station for the settlement.  " +
      	"Several heavily armored gnomes can usually be found here, " +
      	"unless they are out maintaining order.  Or eating donuts, of " +
      	"course.  A pole is planted here, extending up through a hole in " +
	"the ceiling.", 70));

    INSIDE;
    LIGHT;
    
    add_item(({"cavern", "cave", "caves"}), "A small gnome-made chamber " +
	"connected to the main cavern.\n");
    add_item("pole", "A slippery pole which extends all the way up to the " +
	"third floor!  Pillows lie around the base here.\n");
    add_item(({"pillow", "pillows"}), "Pillows lie around the pole in " +
	"the center of the room.\n");

    add_cmd_item(({"up", "up the pole", "pole"}), "climb", "@@climb");

    add_exit(TDIR + "cavern9", "west", 0);
    add_exit(TDIR + "living5", "north", 0);
    reset_room();
}

reset_room()
{
    if (!present("guard", TO)) fillit();
}

wayout() { return "north east"; }
tohelp() { return "done"; }
fromhelp() { return "east"; }

fillit()
{
    int i;
    for (i = 0; i < 3; i++)
    	clone_object(MON + "guard")->move_living("xxx", TO);
}

climb()
{
    if (random(100) < TP->query_skill(SS_CLIMB))
    {
	write("You manage to climb the pole!\n");
	TP->move_living("climbing the pole", TDIR + "guard1");
	return 1;
    }
    write("You try but fail to climb the pole.\n");
    say(QCTNAME(TP) + " tries in vain to climb the pole.\n");
    return 1;
}
