inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("This area seems very quiet, yet not entirely still."
      + " The mud around a few of the puddles looks disturbed in some"
      + " way.");

    add_item(({"mud","dirt"}), BSN("Looking a bit more closely at the"
      + " muddy ground, you notice that the mud contains depressions"
      + " very similar in shape to human feet. Perhaps they are"
      + " footprints."));
    add_item(({"footprint","footprints","depression","depressions"}),
        BSN("Perhaps they are footprints. They seem to head in a"
      + " southeasterly direction."));

    make_deadtree();

    add_exit(ENTWASH_DIR + "ent4b", "south");
    add_exit(ENTWASH_DIR + "ent4c", "southeast");
    add_exit(ENTWASH_DIR + "ent4d", "east");
    add_exit(ENTWASH_DIR + "ent3a", "west");
}
