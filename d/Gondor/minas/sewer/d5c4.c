inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a dark and narrow deadend "
      + "branching off from the tunnel to the southwest. "
      + "A small niche opens in the west wall.");
 
    add_exit(MINAS_DIR + "sewer/d2c4",   "southwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/r4c4",   "west", 0, 0);


    add_item( ({ "small niche", "niche", "west wall" }),
        BSN("A shallow niche is set into the west wall, " +
            "just about head-high."));
    floor("southwest");
    passage("southwest");
}

