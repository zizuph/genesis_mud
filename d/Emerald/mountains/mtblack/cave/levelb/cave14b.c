/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    set_short("This is a very dark place. " +
        "Lets face it, you can see very little");
    set_long("   " +
        "The cave seems to widen out towards the north. " +
        "The darkness seems to permeate everywhere in this part of " +
        "the cave. You can't really see very much at all here.\n\n");

    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n"
        );
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

    add_exit(THIS_DIR+"cave15b", "north", 0, 1);
    add_exit(THIS_DIR+"cave12b", "southeast", 0, 1);
}
