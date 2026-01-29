inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("A swiftly flowing stream runs to the south here,"
      + " beyond which can be seen the beginnings of the plains of"
      + " Anorien, which run some distance in that direction.");

    add_item(({"plains","plains of anorien"}), BSN(
        "The mist has broken to the south, allowing for a glimpse of"
      + " the wilds of Anorien. The plains extend for a great distance"
      + " to eventually meet with the Greenway."));
    add_item(({"stream"}), BSN("The stream to the south still carries"
      + " a good portion of the flow and current of the Entwash. It"
      + " runs east for a while, and then disappears north into the"
      + " mists."));
    add_item(({"greenway"}), BSN("The Great West road, otherwise known"
      + " as the Greenway lies very far to the south, and cannot be"
      + " seen from here."));

    make_deadtree();

    add_exit(ENTWASH_DIR + "ent3f", "northeast");
    add_exit(ENTWASH_DIR + "ent3d", "northwest");
}
