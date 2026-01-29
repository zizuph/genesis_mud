/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    set_short("This is a very dark place. " +
        "Unnaturally dark, you might well think..."); 
    set_long("   " +
        "This is a very dark place. The darkness seems to surround " +
        "you everywhere you go, trying to suffocate you. It is hard " +
        "to see your feet, let alone the walls or the roof. The way " +
        "to the southwest seems lighter, but not the way to the north, " +
        "which, if anything, seems a little darker.\n\n");

    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

    add_exit(THIS_DIR+"cave9b", "southwest", 0, 1);
    add_exit(THIS_DIR+"cave12b", "north", 0, 1);
}
