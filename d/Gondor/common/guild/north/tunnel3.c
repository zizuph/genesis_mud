#pragma save_binary

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/guild/north/northern_hq.h"

void
create_gondor()
{
    set_short("the southern passageway");
    set_long(BS("The passageway is quite dark here. Only a dim "+
      "light from further down the passage reaches here. The walls "+
      "are smooth and wet, and in some places you can even feel "+
      "water trickling down. The passage seems to be heading straight "+
      "northeast and southwest.\n"));

    add_item("passage", "The passage is rather dark and wet here. "
      + "There seems to be some flickering lights further northeast.\n");
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR + "tunnel2", "northeast", 0);
    add_exit(RANGER_NORTH_DIR + "tunnel4", "southwest", 0);
}

