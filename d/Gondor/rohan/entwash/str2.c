inherit "/d/Gondor/rohan/entwash/stream";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_extra_long("A bit to the south the river is visible bending"
      + " in a more eastward direction. The plains of the East Emnet"
      + " extend for miles away to the east, eventually to meet with"
      + " the mouths of the Entwash.");

    set_flow("southeast");

    add_exit("/d/Gondor/rohan/plains/j10", "west");
    add_exit(ENTWASH_DIR + "str1", "north");
    add_exit(ENTWASH_DIR + "str3", "southeast");
}
