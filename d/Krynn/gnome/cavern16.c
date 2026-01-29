#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/std/room";

void
create_room()
{
    set_short("Gnomish Industries Explosives Lab");
    set_long(BS("This is the beginnings of the explosives" +
	" research facility for Gnomish Industries. This part" +
	" of the caverns are as yet unfinished. There is nothing" +
	" much here except roughly hewn holes in the bedrock which" +
	" might be for the expansion of further rooms of the" +
	" facility.", 70));
    add_exit(TDIR + "cavern15", "out", 0);
    INSIDE;
    LIGHT;
}

