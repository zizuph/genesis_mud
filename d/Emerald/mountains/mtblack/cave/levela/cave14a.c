/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("This cave has stalactites hanging down from the roof");
    set_long("   " +
        "This room is very cold, but still has lichen growing in places. " + 
        "There are drops of water splashing down " +
        "all around you. In fact, when you look up, you can see that " +
        "there are stalactites hanging from the ceiling, which have " +
        "been built up over the centuries by the water that is " +
        "dripping down from the roof of the cave. There is a large hole in " +
        "the centre of the cave. You can't hear the drops of water landing " +
       "at the bottom, so you guess it must be quite deep.\n\n");

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
    add_item(({"stalactite","stalactites"}),
        "You can see several dozens of large stalactites " +
        "hanging from the ceiling. They are dripping with " +
        "water, and still probably growing longer.\n");
    add_item(("hole"),"It is a large hole leading down. " +
        "It looks like you could make your way down it.\n");

    add_exit(THIS_DIR+"cave13a", "west", 0, 1);
    add_exit(CAVE_DIR + "levelb/cave5b", "down", 0, 4);
}
