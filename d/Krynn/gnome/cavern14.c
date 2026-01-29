#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("First floor tunnel");

    set_long(BS("You are near the end of a tunnel leading from the" +
	" first floor "+
      	"landing area into the bedrock.  There is a faint smell of "+
      	"sulphur here, and noticeable scorch marks along the walls.", 70));
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid" +
	" rock, this tunnel leads in to one of the gnomish\nresearch" +
	" labs.  It extends a long way from the main cavern.");
    add_item(({"mark", "marks"}), "Long black marks, radiating from" +
	" further to the west...  The air seems cool,\nso the blasts" +
	" could not have been too recent.\n");
    INSIDE;
    LIGHT;
    add_exit(TDIR + "cavern15", "west", 0);
    add_exit(TDIR + "cavern13", "east", 0);
}

wayout() { return "east west"; }
tohelp() { return "west"; }
fromhelp() { return "east"; }
area() { return "Hereonthisfloor"; }
