inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This branch of the tunnel system is coming to "
      + "an end here. The tunnel is leading back southeastwards. "
      + "In the roof a drain is leading down from the surface.");

    add_exit(MINAS_DIR + "sewer/d8c4", "southeast", 0, 0);

    floor("southeast");
    passage("southeast");

    roof("drain");
}

