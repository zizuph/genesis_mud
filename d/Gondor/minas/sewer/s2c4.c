inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("Two branches of the tunnel, one from the "
      + "northeast and the other from the southwest, join here and "
      + "continue down to the southeast into a small passage. This "
      + "passage is blocked by a massive metal grid.");
 
    add_exit(MINAS_DIR + "sewer/s1c4",   "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/gatec4", "southeast", "@@grid_block@@", 0);
    add_exit(MINAS_DIR + "sewer/s3c4",   "southwest", 0, 0);

    floor("southeast");
    passage("southeast");
    grid("southeast");
    roof();
}

