inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The main tunnel is running from the northwest "
      + "through a small bend to the south. A smaller tunnel is "
      + "branching off to the northeast.");
 
    add_exit(MINAS_DIR + "sewer/d2c4",   "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/n2c4",   "south",     0, 0);
    add_exit(MINAS_DIR + "sewer/n4c4",   "northwest", 0, 0);

    floor("south");
    passage("south");
    roof();
}

