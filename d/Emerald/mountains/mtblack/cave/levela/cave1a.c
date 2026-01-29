/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Dead end cave");
    set_long("   " +
        "The roof of the cave is quite low, so you have to duck " +
        "down while you walk, or run the risk of banging your head. " +
        "This is a dead end. The only exit you can see is back the way " +
        "that you came in. There is lichen growing on the walls.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and crumbles to dust when you touch it.\n");
    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "There is some lichen growing on the wall.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock. There is some lichen growing on the floor.\n");

    add_exit(THIS_DIR+"entrance", "east", 0, 1);
}
