inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("The air here seems somehow denser than in other"
      + " areas of this marsh. A quiet has descended on the area, and"
      + " only the croaking of a nearby toad breaks the lull of the"
      + " silent bog.");

    add_item(({"toad","toads","frog","frogs"}), BSN(
        "As is typical for such creatures, the toad is well out of"
      + " sight. Only its occasional gasp makes you aware that it is"
      + " near."));
    add_item(({"air"}), BSN("The mist here is markedly denser than in"
      + " other areas of the bog. Perhaps it is due to some emenations"
      + " from the soil."));

    add_exit(ENTWASH_DIR + "ent3c", "north");
    add_exit(ENTWASH_DIR + "ent3e", "southeast");
}
