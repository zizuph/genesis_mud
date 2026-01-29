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
        "But you think you can hear something. There seems to be " +
        "something shuffling around to the east. Or maybe it is just " +
        "the way the caves make you hear yourself. Well, theres only " +
        "one way to find out.\n\n");

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

    add_exit(THIS_DIR+"cave6b", "southeast", 0, 1);
    add_exit(THIS_DIR+"cave8b", "west", 0, 1);
    add_exit(THIS_DIR+"cave11b", "northeast", 0, 1);
}
