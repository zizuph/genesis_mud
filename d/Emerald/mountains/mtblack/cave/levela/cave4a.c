/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("This part of the cave has three exits");
    set_long("   " +
        "There is very little to see in this part of the cave. " +
        "Of course, normally there would not be enough light to see " +
        "anything, but even though you can see a little, you " +
        "cannot see much more than the cold rock walls of the " +
        "cave that surround you. You do, however, notice some lichen " +
        "growing in various parts of the cave.\n\n");

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

    add_exit(THIS_DIR+"cave3a", "west", 0, 1);
    add_exit(THIS_DIR+"cave5a", "east", 0, 1);
    add_exit(THIS_DIR+"cave9a", "north", 0, 1);
}
