/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dead end cave");
    set_long("   " +
        "This cave is a dead end. There are some paintings on the wall, " +
        "however, that suggest someone has been here before you. " +
        "Your sharp eye also notices some footprints on the ground, " +
        "which seem to confirm your suspicions.\n\n");

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

    add_item(({"floor","footprints","footprint","ground"}),
        "You look at the floor of the cave carefully, to see " +
        "someones grubby footprints all over the floor.\n");

    add_item(({"cave painting","cave paintings","paintings","painting",
        "paint"}), "On the walls of the cave are some rather " +
        "primitive paintings. They seem to depict the day to day " +
        "life of a very primitive people, showing things like " +
        "hunting, lighting fires, and climbing trees. These " +
        "paintings also seem to have kept rather too well for " +
        "how old they should be.\n");

    add_exit(THIS_DIR+"cave2a", "south", 0, 1);
}
