/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/d/Emerald/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_emerald_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave");    
    set_long("   "+
        "You have three possible choices of where to go in this cave. " +
        "Of course if you're trying to avoid Ogres you would not be here " +
        "in the first place, and there should be plenty of Ogres around " +
        "not too far from here.\n\n");

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
    
    add_exit(THIS_DIR+"cave25c", "north", 0, 1);
    add_exit(THIS_DIR+"cave16c", "southwest", 0, 1);
    add_exit(THIS_DIR+"cave17c", "southeast", 0, 1);
}

