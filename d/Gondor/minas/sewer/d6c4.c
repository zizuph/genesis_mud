inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a smaller tunnel branching off from "
      + "the main tunnel that lies to the southwest. This branch "
      + "makes a turn to the east while a small recess "
      + "is branching off to the west.");
 
    add_exit(MINAS_DIR + "sewer/d7c4",   "east", 0, 0);
    add_exit(MINAS_DIR + "sewer/n5c4",   "southwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/r2c4",   "west", 0, 0);

    floor("southwest");
    passage("southwest");
}

