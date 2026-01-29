/* This is the Grunts library.    */
/* Recoded 21/09/95 by Tulix III. */

inherit "/std/room";

#include "default.h"

void
create_room()
{
    set_short("Grunts library");
    set_long(
        "   This is the Grunts guild library. Coming here is a bit " +
        "of a waste of time at the moment though, as it is rather " +
        "empty. In fact, there is not a book in sight. " +
        "I guess you'll just have to wait until someone writes one.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(THIS_DIR+"main", "west", 0, 1);

    add_item(({"walls","wall"}),
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n");
    
    add_item(({"roof","ceiling"}),
        "What you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

}
