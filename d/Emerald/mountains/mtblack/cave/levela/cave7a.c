/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A tunnel like cave");
    set_long("   " +
        "This cave is like a tunnel, that gradually curves round, " +
        "so that you can't see exactly what is around the corner. " +
        "The air in this place is quite cold: this is mainly due " +
        "to the lack of sunlight, which does not reach down here. " +
        "The walls seem fairly damp here, too.\n\n");

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

    add_exit(THIS_DIR+"cave6a", "west", 0, 1);
    add_exit(THIS_DIR+"entrance", "south", 0, 1);
}
