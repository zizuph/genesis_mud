inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include <macros.h>
#include "/d/Gondor/defs.h"

/* Prototypes */
void reset_room();

object cocoon;

void create_room()
{
    add_exit(MORGUL_DIR + "tunnel/hiding1", "northeast", 0, 2);

    make_the_room(" The cave continues to the northwest where it grows smaller. "+
        "Between here and the rest of the cave, a vast cobweb is hanging. ");

    add_item(({"web","cob-web","cobweb","cob web","rent"}), BSN(
        "Across the width and height of the cave to the northwest a vast web is spun, " +
        "orderly as the web of some huge spider, but denser-woven and far greater, and with " +
        "threads as thick as a rope. The cords of the web glitter strangely in the shine " +
        "of your light source. Someone has cut a great rent through the middle of the web " +
        "through which you could walk to the northeast."));
    add_item(({"thread","threads","cord","cords"}), BSN(
        "Each cords of the giant web is as large as a rope. The material of which the " +
        "threads are made seems to be very tough, hard like metal, but resilient at the " +
        "same time. Most of the cords are covered by a gleaming substance."));

    seteuid(getuid());
    reset_room();
}

void init()
{
    ::init();
}

void add_stuff()
{
    if(!cocoon)
    {
        cocoon = clone_object(MORGUL_DIR + "obj/cocoon");
        cocoon->move(TO);
    }
}

void reset_room()
{
    add_stuff();
}
