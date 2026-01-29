inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a smaller tunnel branching off from "
      + "the main tunnel that lies to the southwest. This tunnel "
      + "makes a turn to the northwest while an even narrower one "
      + "is branching off to the northeast.");
 
    add_exit(MINAS_DIR + "sewer/d5c4",   "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/n3c4",   "southwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/d3c4",   "northwest", 0, 0);

    floor("southwest");
    passage("southwest");
}

