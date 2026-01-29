#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/std/room";

create_room()
{
    set_short("Near third floor landing");

    set_long(BS("You are near the third floor landing area.  Once " +
      	"away from the main cavern, the noise level drops considerably.  " + 
      	"There is a sign pointing south. This tunnel curves " +
	"northward to the west.", 70));
    INSIDE;
    LIGHT;
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock, " +
	"this tunnel leads in to one of the gnomish\nresearch labs. " +
	"It extends a long way from the main cavern.");
    add_item("sign", "You can read it.\n");
    add_cmd_item("sign", "read", "The sign reads:\n" +
	"The Gnomes' Inventor Guild.\n");
    add_exit(TDIR + "cavern33", "northwest", 0);
    add_exit(TDIR + "cavern31", "east", 0);
    add_exit("/d/Krynn/guilds/gnomes/rooms/tunnel1.c", "south", 0);
}

wayout() { return "east northwest"; }
tohelp() { return "northwest"; }
fromhelp() { return "east"; }
area() { return "Hereonthisfloor"; }
