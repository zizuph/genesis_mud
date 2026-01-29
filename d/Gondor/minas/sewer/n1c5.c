inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("Two branches of the tunnel, one from the "
      + "northwest and the other from the southeast, join here and "
      + "continue down to the northeast into a small passage. This "
      + "passage is blocked by a massive metal grid.");
 
    add_exit(MINAS_DIR + "sewer/n2c5",   "northwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/gatec5", "northeast", "@@grid_block@@", 0);
    add_exit(MINAS_DIR + "sewer/c1c5",   "southeast", 0, 0);

    floor("southeast");
    passage("southeast");
    grid("northeast");
}

