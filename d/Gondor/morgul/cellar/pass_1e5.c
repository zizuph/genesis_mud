/*
 * /d/Gondor/morgul/cellar/pass_1e5.c
 * A passage on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 18-Oct-1995
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("dark narrow passage");
    set_extra_long("The tunnel comes to a sudden end here. A flight "
      + "of stairs is leading down inside an archway in the north "
      + "wall. Two more archways are opening to the northeast and "
      + "the southeast, leading into dungeons.");

    add_walls();
    add_floor();
    add_archways("northeast", "southeast");
    add_c_passage("southwest");
    add_down_archway();
    add_ceiling();

    add_exit(CELLAR_DIR + "dung_1e2", "northeast", 0, 1);
    add_exit(CELLAR_DIR + "dung_1e3", "southeast", 0, 1);
    add_exit(CELLAR_DIR + "pass_1e4", "southwest", 0, 1);
    add_exit(CELLAR_DIR + "pass_2e2", "down",      0, 1);
}

