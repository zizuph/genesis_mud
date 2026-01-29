inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("This is an area of the fens which runs right up"
      + " to the great river Anduin. To the northeast, the mists have"
      + " lifted to allow a good look at the waterway, and even the"
      + " far bank.");

    add_item(({"river","anduin","river anduin","great river anduin"}),
        BSN("Even at this fairly narrow point in its eastward flow,"
      + " the great river flows with great breadth and majesty. The"
      + " ever present mists of this fen prevent a view of its east"
      + "erly travel, but the far bank is visible in the distance."));
    add_item(({"bank","far bank"}), BSN(
        "The bank looks miles away, and yet is clearly visible across"
      + " the water of the great river. A long cloud hangs over the"
      + " other side of the river, for there is the great swamp of"
      + " Wetwang, also known as the Nindalf."));

    add_exit(ENTWASH_DIR + "ent3h", "west");
    add_exit(ENTWASH_DIR + "ent3f", "south");
}
