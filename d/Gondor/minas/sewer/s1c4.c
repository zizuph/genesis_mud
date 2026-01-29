inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The tunnel is running in a straight passage "
      + "down from the northeast to the southwest.");
    add_exit(MINAS_DIR + "sewer/c1c4", "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/s2c4", "southwest", 0, 0);

    floor("southwest");
    passage("southwest");
    roof();
}

