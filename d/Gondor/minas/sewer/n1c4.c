inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The tunnel is running in a straight passage from "
      + "the northwest down to the southeast.");

    add_exit(MINAS_DIR + "sewer/n2c4",   "northwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/c1c4",   "southeast", 0, 0);

    floor("southeast");
    passage("southeast");
}

