/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("This part of the cave is a curved tunnel");    
    set_long("   " +
        "This part of the cave seems to be a tunnel that gradually " +
        "curves round to take you to another part of the cave. " +
        "The walls of the cave are quite damp here, and it is cold. " +
        "You get the strange feeling that you are being watched. " +
        "When you look around, you realise that you must be imagining " +
        "things. Maybe it is just because these caves are a little bit " +
        "scary.\n\n");

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

    add_exit(THIS_DIR+"cave3b", "west", 0, 1);
    add_exit(THIS_DIR+"cave8b", "northeast", 0, 1);
}
