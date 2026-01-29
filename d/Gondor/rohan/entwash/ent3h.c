inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("North of here, the river Anduin flows slowly to"
      + " the east, quietly accepting the streams of the Entwash."
      + " Very little of the river is visible through the mist, and"
      + " all that is readily apparent is that the ground falls away.");

    add_item(({"river","river anduin","anduin"}), BSN(
        "The occasional leaf floating by in the current is all that"
      + " helps to identify this mist shrouded waterway as anything"
      + " other than a large pool or lake."));

    add_exit(ENTWASH_DIR + "ent3i", "south");
    add_exit(ENTWASH_DIR + "ent3g", "east");
}
