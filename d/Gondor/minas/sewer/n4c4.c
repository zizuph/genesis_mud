inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The main tunnel is running from the northwest "
      + "to the southeast. In the southwest wall, there is a small "
      + "recess.");
 
    add_exit(MINAS_DIR + "sewer/n3c4",   "southeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/r1c4",   "southwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/n5c4",   "northwest", 0, 0);

    recess("southwest");
    floor("southeast");
    passage("southeast");
}

