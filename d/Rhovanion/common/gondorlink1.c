inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Border of Rhovanion");
    set_long("You have reached the border of the land called Rhovanion. "+
             "It stretches vast and dangerous to the north while to the south "+
             "starts the land known under the name of Gondor.\n");

    add_exit(ANDUIN_DIR + "togon5", "north");
    add_exit("/d/Gondor/common/rholink1", "southeast");
}
