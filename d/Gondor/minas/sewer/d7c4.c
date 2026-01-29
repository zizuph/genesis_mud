
inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This branch of the tunnel system is coming to "
      + "an end here. The tunnel is leading back westwards. "
      + "In the roof a drain is leading down from the surface.");

    add_exit(MINAS_DIR + "sewer/d6c4", "west", 0, 0);

    floor("west");
    passage("west");

    roof("drain");
}

