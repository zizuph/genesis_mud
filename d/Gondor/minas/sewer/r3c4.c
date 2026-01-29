inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a small recess branching off from the "
      + "tunnel to the east. A drain in the roof is leading "
      + "down into the tunnel from the surface.");

    add_exit(MINAS_DIR + "sewer/d3c4", "east", 0, 0);

    floor("east");
    passage("east");

    roof("drain");
}

