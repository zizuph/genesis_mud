inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("Great Hall");
    set_long(BSN(
        "This must be the largest hall of the house. It is about twice as "
      + "long from west to east as it is wide. The vaulted ceiling is far "
      + "above your head, the walls are covered by colourful tapestries. "
      + "A doorway leads into the entryhall to the south, and an arched "
      + "opening out into a garden to the east."));

    add_item(({"walls", "stone walls", "tapestries", }), BSN(
        "The stone walls are covered by valuable tapestries that show "
      + "colourful floral patterns."));
    add_item(({"floor", "carpet"}), BSN(
        "The stone floor is covered by rectangular grey stone tiles."));
    add_item(({"doorway", "door"}),
        "It leads south into the entryhall.\n");
    add_item(({"arch", "opening", "archway", "arched opening"}),
        "It leads out into a garden to the east.\n");

    add_exit(MINAS_DIR+"houses/g2ncrc4","east",0,0);
    add_exit(MINAS_DIR+"houses/h1ncrc4","south",0,0);

    add_prop(ROOM_I_INSIDE, 1);
}

