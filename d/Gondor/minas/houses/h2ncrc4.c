inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("Dining Hall");
    set_long(BSN(
        "A long table in the middle of the room marks this as the dining "
      + "hall. A large fireplace in the east wall north of the doorway "
      + "can be used to light and heat the hall."));

    add_item(({"walls", "stone walls", "tapestries", }), BSN(
        "The stone walls are covered by valuable tapestries that show "
      + "colourful floral patterns."));
    add_item(({"floor", "ground", "tiles", }), BSN(
        "The floor is covered by stone oblong black stone tiles."));
    add_item("table",BSN(
        "The table is very long so that all members of a large household "
      + "can sit down at it. Right now it is empty."));
    add_item(({"doorway", "door"}),
        "The doorway leads back into the entryhall.\n");
    add_item(({"fire place", "fireplace"}), BSN(
        "The fireplace is in the east wall of the hall, probably so that "
      + "it can heat more rooms of the house than just this hall when it "
      + "is lit."));

    add_exit(MINAS_DIR+"houses/h1ncrc4","east",0,0);

    add_prop(ROOM_I_INSIDE, 1);
}

