/*      This is the farmhouse which Mardil lives in.
 *      It is just to the west of the Ring road around pelargir
 *
 *
 *      Copyright(C) 1996 Jim Fraser  ----  Theory
 *
 */

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h";


void
create_room()
{
    set_long(BSN("The farmhouse is a warm and inviting place.  The fire "
        + "burning in the hearth gives off a lot of heat, and casts a warm "
        + "glow about the small room.  The sleeping quarters are upstairs, "
        + "in the hayloft, and there is a ladder leading up to them.  There " 
        + "are a number of small but comfortable chairs "
        + "near the fire, and there is a painting above the fireplace."));
    set_short("Inside the farmhouse.");

    add_exit(LEB_DIR + "rroad/rfield4", "out", 0, 2);
    add_exit(LEB_DIR + "rroad/rfarmup", "up", 0, 2);

    add_item(({"ladder", "hayloft",}),BSN("The ladder leading to the hayloft "
        + "seems to be well crafted and should be able to hold the weight of " 
        + "any man."));
    add_item(({"painting", "picture",}),BSN("The picture above the fire shows "
        + "a room with 2 brightly painted doors and 2 colourfully dressed men. "
        + "There is also a third man in the painting, and this man is garbed "
        + "far more commonly. He seems to be thinking hard about something."));
    add_item(({"fireplace", "hearth",}),BSN("The fireplace and chimney are "
        + "made from the roughly hewn grey stone of the nearby mountains. "
        + "While it looks to be badly made, by the burn marks on the rocks, "
        + "it is easy to tell that it has stood for a very long time."));
    add_item(({"fire",}),BSN("The fire is sending a lot of heat into the room "
        + "and there is a cast iron pot sitting over it."));
    add_item(({"pot", "cast iron pot",}),BSN("Whatever is cooking in the pot "
        + "smells very good. If you are very nice to whoever lives here, you "
        + "might get an invitation for dinner!"));

    add_item(({"farmhouse", "house",}),BSN("The house is simply an oridinary "
        + "farmhouse, simple in its design yet functional."));
}
