
inherit "/std/room.c";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <std.h>

void
create_room()
{
    set_short("Unfinished Swamp");
    set_long("Unfinished Swamp ... maybe you could work on it.\n");
    add_exit(SOL_DIR + "/graves/wrkrm.c","west","@@west_msg");
    OUTSIDE;
    LIGHT;
}

int
west_msg()
{
    write("You slog through lots of uncharted, dark, trecherous \n"
	  + " swamp.  To bad it is in so much chaos ... perhaps a Krynn\n"
	  + " Wizard will change this soon (HINT!!).  After quite some\n"
	  + " time the swamp becomes solid and you come out in the back\n"
	  + " of the graveyard and from there back to the workroom.\n"
	  + " (who was xak, anyway?)\n");
    return 0;
}

