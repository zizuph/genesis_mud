inherit "/d/Gondor/pelargir/sewers/sewer.c";

#include "/d/Gondor/defs.h"

void
create_sewer()
{
    set_extra_long("To the southwest, a metal grid blocks "
      + "the tunnel, probably to prevent unauthorized personnel from "
      + "entering the sewers. In the northwest wall a small recess "
      + "branches off from the tunnel.");

    add_exit(PELAR_DIR + "sewers/dock_ent", "northeast", 0, 1);
    //add_exit(PELAR_DIR + "sewers/dock2",    "southwest", "@@grid_block@@", 1);
    add_exit(PELAR_DIR + "misc/sewguild",   "northwest", 0, 1);

    floor("northeast");
    passage("northeast");
    roof();
    grid("southwest");
    recess("northwest");
}


