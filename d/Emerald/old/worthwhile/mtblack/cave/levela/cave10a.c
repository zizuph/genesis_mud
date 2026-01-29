/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("This part of the cave has three dark exits");
    set_long("   " +
        "Brrrrrr! You rub your hands together, as it is really cold. " +
        "There is a lot more water in this cave, probably because " +
        "of the temperature. Large drops of water have formed on " +
        "the roof of the cave, and every now and then one falls " +
       "down into a puddle, making a little splash as it hits.\n\n");

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
    add_item(({"puddle","puddles"}),
        "These are ordinary puddles, containing ordinary water.\n");

    add_exit(THIS_DIR+"cave6a", "south", 0, 1);
    add_exit(THIS_DIR+"cave11a", "east", 0, 1);
    add_exit(THIS_DIR+"cave13a", "north", 0, 1);
}
