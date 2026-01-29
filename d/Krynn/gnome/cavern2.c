#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("In a tunnel");

    set_long(BS("You are passing through a tunnel cut into the stone.  " +
      "The noises of the elevator to the surface filter in from the west.  " +
      "To the east the tunnel continues.", 70));

    add_item("tunnel", "Hewn out of the rock, the tunnel walls curve " +
	"and meet above your head.\n");
    INSIDE;
    LIGHT;
    add_exit(TDIR + "cavern3", "east", 0);
    add_exit(TDIR + "cavern1", "west", 0);
}

wayout() { return "east west"; }
tohelp() { return "east"; }
fromhelp() { return "west"; }
area() { return "Inthemaincaverns"; }
