inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object  door;

void
create_room()
{
    set_short("a house in a village in Emyn Arnen");
    set_long(BSN("Long ago this house must have belonged to a servant "
      + "of the House of Hurin. It is rather small, and through long "
      + "neglect in bad repair. A narrow doorway leads to the north "
      + "while the main door is to the south."));
    add_item(({"ceiling", "roof"}), BSN(
        "The roof looks like it will fall down every moment. Through "
      + "holes in it you can see the sky."));
    add_item(({"ground", "floor"}), BSN(
        "The floor is covered by rubble and dirt. The wooden planks " +
        "which once covered the ground have rotten away in places so " +
        "that the earth below is uncovered."));
    add_item(({"rubble", "dirt", "earth"}), BSN(
        "Just rubble and dirt. It stinks, and there is certainly " +
        "nothing valuable among it."));
    add_item(({"window", "windows", "door"}), BSN(
        "All that remains of the windows and the door leading south " +
        "onto the street are empty holes in the wall."));

    add_exit(ITH_DIR + "emyn-arnen/house3b", "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrdn",    "south", 0, 1);

    add_prop(ROOM_I_INSIDE, 1);
}

