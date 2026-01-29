inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("Many streams and patches of water wind their way"
      + " through this area, most of them running to the northeast. In"
      + " that direction, you sense a change in the terrain.");

    add_item(({"terrain"}), BSN("To the north, the fog seems to lift"
      + " slightly, as if some wide space opens in that direction."));

    add_exit(ENTWASH_DIR + "ent2a", "southwest");
    add_exit(ENTWASH_DIR + "ent2c", "northeast");
}
