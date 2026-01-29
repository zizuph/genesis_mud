/* This a secret passage leading from the Grunts guild to the cave entrance */
/* Coded due to lack of light in the rest of the caves by Tulix 1/4/1993    */
/* Recoded on 21/08/95 by Tulix III.                                        */

inherit "/std/room";

#include "default.h"
#include "../guild.h"

public void
create_room()
{
    set_short("secret passage");
    set_long(
        "   There seems to be daylight coming from up above you somewhere. " +
        "It is pleasantly warm in this cave, and the air is not quite as " +
        "still as it is in the deeper parts of the cave. There is a hole " +
        "in the roof of the cave that is probably just big enough to " +
        "squeeze through.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(THIS_DIR + "secret_passage2c", "northeast", 0, 1);
    add_exit(THIS_DIR + "secret_passage1b", "up", 0, 1);


    add_item(({"walls","wall"}),
        "There are torches fixed on both walls of the cave. " +
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n");
    
    add_item(({"roof","ceiling"}),
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

    add_item(({"torch","torches"}),
        "The torches are fixed firmly to the wall, and cannot be taken.\n");

}
