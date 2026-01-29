/* The storage room for the Grunts shop. Mainly stolen from the examples. */
/* Recoded on 21/08/95 by Tulix III.                                      */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "default.h"
#include "../guild.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("This is the Grunts shop store room");
    set_long(
        "This is the store room of the shop " +
        "in the Grunts guild. Only wizards are allowed in here.\n");

    add_exit(THIS_DIR + "shop", "up", 0, 1);

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    add_item(({"walls","wall"}),
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

}
