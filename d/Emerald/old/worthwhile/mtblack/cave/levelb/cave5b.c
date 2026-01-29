/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("This cave has stalagmites growing from the floor");    
    set_long("   " +
        "There are large drips of cold water falling down " +
        "all around you, a lot of them coming down through a large " +
        "hole in the roof of the cave. Because of the amount of water " +
        "that has dripped down over the centuries, large stalagmites " +
        "have grown upwards from the floor. The water that drips down " +
        "into here seems to tickle down to the tunnel leading east. " +
        "It is very cold in here.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
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
    add_item(({"stalagmite","stalagmites"}),
        "You are surrounded by stalagmites. There are big ones, " +
        "small ones, short ones, fat ones and thin ones. They all " +
        "look quite old, and are probably still growing.\n");
    add_item(("hole"),"It is a large hole in the roof of the cave" +
        ". A way up, maybe?\n");

    add_exit(CAVE_DIR + "levela/cave14a", "up", 0, 4);
    add_exit(THIS_DIR+"cave6b", "east", 0, 1);
}
