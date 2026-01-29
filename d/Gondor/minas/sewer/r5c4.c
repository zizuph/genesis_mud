inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a small recess branching off from the "
      + "tunnel to the southeast. A drain in the roof is leading "
      + "down into this recess from the surface.");

    add_exit(MINAS_DIR + "sewer/s4c4", "southeast", 0, 0);

    floor("southeast");
    passage("southeast");

    roof("drain");
}

