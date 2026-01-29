#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Near second floor landing");

    set_long(BS("You are in an east-west tunnel of the gnomish caverns.  " +
      "Shouts and clanging come from the west.  To the east the tunnel " +
      "opens considerably.", 70));
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock," +
	" this tunnel leads in to one of the gnomish\nresearch labs.  It" +
	" extends a long way from the main cavern.");
    INSIDE;
    LIGHT;
    add_exit(TDIR + "cavern24", "west", 0);
    add_exit(TDIR + "cavern22", "east", 0);
}

wayout() { return "east west"; }
tohelp() { return "west"; }
fromhelp() { return "east"; }
area() { return "Hereonthisfloor"; }

