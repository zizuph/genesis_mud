inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a small recess branching off from the "
      + "main tunnel of the sewers to the northeast. In the roof "
      + "of the tunnel, a drain leading down from the surface is "
      + "visible.");

    add_exit(MINAS_DIR + "sewer/n4c4", "northeast", 0, 0);

    floor("northeast");
    passage("northeast");

    roof("drain");
}

