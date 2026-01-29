#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Near second floor landing");

    set_long(BS("This tunnel leads from the second floor landing area " +
      	"into the bedrock.  You hear a great deal of noise coming from " +
      	"further west.", 70));
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock," +
	     " this tunnel leads in to one of the gnomish\nresearch labs." +
	     "  It extends a long way from the main cavern.\n");
    INSIDE;
    LIGHT;
    add_exit(TDIR + "cavern23", "west", 0);
    add_exit(TDIR + "cavern21", "east", 0);
}

wayout() { return "east west"; }
tohelp() { return "west"; }
fromhelp() { return "east"; }
area() { return "Hereonthisfloor"; }
