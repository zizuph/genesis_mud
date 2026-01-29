inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The narrow tunnel comes down from the "
      + "northeast, runs through a bend here and continues "
      + "down to the southeast. A narrow recess is opening "
      + "in the west wall.");
 
    add_exit(MINAS_DIR + "sewer/d4c4",   "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/r3c4",   "west", 0, 0);
    add_exit(MINAS_DIR + "sewer/d2c4",   "southeast", 0, 0);

    floor("southeast");
    passage("southeast");
}

