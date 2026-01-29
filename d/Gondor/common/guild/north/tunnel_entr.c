#pragma save_binary

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/guild/north/northern_hq.h"

void
create_gondor()
{
    set_short("in the tunnel opening");
    set_long(BS("A little light comes in through the bushes above, allowing you "+
      "a dim view of a passage sloping off into darkness down towards the " +
      "northeast. The walls of the tunnel are smooth and wet, and a dank, musty "+
      "smell of marsh water dominates the air. There are stone steps here, providing " +
      "an easier exit out through the bushes above.\n"));

    add_item("passage", "The passage is rather dark and wet here. "
      + "The light that is, as well as a draft of fresh air is coming through "
      + "the bushes above.\n");
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR + "tunnel4", "northeast", 0);
    add_exit(ARNOR_DIR + "greenway/swamp", "out", 0);
}
