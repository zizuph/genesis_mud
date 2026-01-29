inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("The water of the fens is running into a large"
      + " waterway here, which can only be the River Anduin. Jutting"
      + " out of the water here, a large boulder stands as a dark"
      + " shadow in the haze.");

    add_item(({"river","waterway","anduin","river anduin"}), BSN(
        "There is no current in the water to the north, and it is"
      + " likely that this is more of a floodbasin than the actual"
      + " river itself. The mist makes it impossible to see very far"
      + " out over the water."));
    add_item(({"rock","boulder","boulders","rocks","shadow"}), BSN(
        "This boulder is probably 6 feet high and weighs many tons."
      + " It is unlike anything else in this terrain, and you get the"
      + " impression that this is only the top of a very large sunken"
      + " fragment."));

    make_deadtree();

    add_exit(ENTWASH_DIR + "ent2b", "southwest");
}
