inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("A swiftly flowing stream lies to the east here as"
      + " it makes its way toward the Anduin. Beyond the stream the"
      + " grasslands of Anorien can be seen extending for miles.");

    add_item(({"stream"}), BSN("This stream is running northward at"
      + " a fairly swift pace. A gully has been dug by its current,"
      + " beyond which the mists have begun to lift to the east."));
    add_item(({"gulley","gullies"}), BSN("The gully carved by the"
      + " swiftly flowing stream is not deep, but still a variance"
      + " in comparison with the general lay of these fens."));
    add_item(({"grasslands","grassland","plain","plains"}), BSN(
        "The land changes quite suddenly on the other side of the"
      + " eastern stream. Tall grasses can be seen growing on the"
      + " far bank, and the mists dissipate in that direction."));

    add_exit(ENTWASH_DIR + "ent3g", "north");
    add_exit(ENTWASH_DIR + "ent3e", "southwest");
}
