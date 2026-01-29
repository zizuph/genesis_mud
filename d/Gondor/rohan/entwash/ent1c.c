inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("The ground here is almost entirely water, and"
      + " it is impossible to travel further north. This seems to be"
      + " some large body of water, and is probably the River Anduin."
      + " Tall reeds and cattails are growing in large clumps in the"
      + " deepening water.");

    add_item(({"water","ground","river","anduin","river anduin"}), BSN(
        "This almost certainly is the great Anduin, which is known to"
      + " flow quite near to this area. The calm water and deep mist"
      + " are enough to make it seem as if this is nothing more than"
      + " the edge of a lake."));
    add_item(({"lake"}), BSN("No, it is not a lake, but the mighty"
      + " Anduin flowing to meet with the sea!"));
    add_item(({"reeds","reed","cattail","cattails"}), BSN(
        "The water to the south was not deep enough for such foliage,"
      + " which is yet more evidence that this is indeed the edge of a"
      + " much more substantial waterway."));

    add_exit(ENTWASH_DIR + "ent1b", "south");
}
