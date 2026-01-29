/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"

void 
create_room()
{
    object door;

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    set_short("This is a very dark place. " +
        "There seems to be a door leading east");
    set_long("   " +
        "This cave is different from all the rest, because in the east " +
        "wall of the cave there is a doorway! You can't image why anybody " +
        "would want to live down here, for it is not exactly " +
        "the most cozy place in the world.\n\n");

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

    add_exit(THIS_DIR+"cave12b", "west", 0, 1);

    door=clone_object(CAVE_DIR + "obj/door13b");
    door->set_key(135876);
    door->move(this_object());
}
