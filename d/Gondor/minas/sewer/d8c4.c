inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a smaller tunnel branching off from "
      + "the main tunnel that lies to the southeast. This tunnel "
      + "continues in a straight line to the northwest.");
 
    add_exit(MINAS_DIR + "sewer/s3c4",   "southeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/d9c4",   "northwest", 0, 0);

    floor("southeast");
    passage("southeast");
    roof();
}

