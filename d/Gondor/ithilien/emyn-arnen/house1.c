inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("a house in a village in Emyn Arnen");
    set_long(BSN("Long ago this house must have belonged to a wealthy " +
        "dunedain in the service of the House of Hurin. Now it has " +
        "been deserted and fallen into disrepair. The roof has collapsed " +
        "on the upper floor, the windows and the door are just " +
        "gaping holes in the front of the house. A dark passage is " +
        "leading into a room in the back."));

    add_item(({"ceiling", "roof"}), BSN(
        "The ceiling of this room seems still to hold, but through " +
        "the hole which once was used by the stairs, one can see " +
        "that the roof of the house has crashed down onto the floor " +
        "above."));
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

    add_exit(ITH_DIR + "emyn-arnen/house1b", "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/vrd2",    "south", 0, 1);
}
