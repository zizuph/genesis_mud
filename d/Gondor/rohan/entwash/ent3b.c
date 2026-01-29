inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("Muddy banks and quiet streams extend off in"
      + " all directions from this point. It is becoming difficult"
      + " to distinguish one direction from the next, and only the"
      + " flow of the streams gives any sense of orientation.");

    add_item(({"bank","banks","muddy bank","muddy banks"}), BSN(
        "These banks are moist and spackled with weeds. The water"
      + " from the streams curve gently between them."));

    add_exit(ENTWASH_DIR + "ent3c", "northeast");
    add_exit(ENTWASH_DIR + "ent3a", "southwest");
}
