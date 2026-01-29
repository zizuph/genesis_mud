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
       "This is one of the darkest places you have ever been inside. You "+
        "cannot even see where your feet are stepping. The situation is "+
        "not a comfortable one. You keep imagining hundreds of holes "+
        "in the cave floor which you cannot see, expecting any second "+
        "that you will step through one and never return...\n\n");

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

    add_exit(THIS_DIR+"cave14b", "northwest", 0, 1);
    add_exit(THIS_DIR+"cave13b", "east", 0, 1);
    add_exit(THIS_DIR+"cave11b", "south", 0, 1);
}
