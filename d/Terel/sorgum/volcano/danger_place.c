inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("near ledge.");
    set_long(BSN(
	"Unfolded below is a desert that seems to have no end.  Black " +
        "caverns and odd crevices are on sheer verticle cliffs, but " +
        "none look accessible to a climber."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANO_DIR + "ledge", "east", 0);
}


