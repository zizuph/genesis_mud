#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/on_lake";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_nen_hithoel()
{
    set_show_area_desc();
    set_loc(5);
    set_extraline("This is just a test room, but it works!");

    add_exit(DELRIMMON_DIR + "lakeside/parth1", "south");
} /* create_nen_hithoel */
