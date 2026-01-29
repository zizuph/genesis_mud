inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The tunnel is coming down from the north here, "
      + "making a slight bend, and continuing to the southeast. "
      + "A smaller tunnel is leading up to the southwest.");
 
    add_exit(MINAS_DIR + "sewer/n3c4",   "north",     0, 0);
    add_exit(MINAS_DIR + "sewer/n1c4",   "southeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/gatec5", "southwest", 0, 0);

    floor("southeast");
    passage("southeast");
}

