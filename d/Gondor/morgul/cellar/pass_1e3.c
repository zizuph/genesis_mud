/*
 * /d/Gondor/morgul/cellar/pass_1e3.c
 * A passage on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 30-jul-1994
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
    set_extra_long("The tunnel makes a bend here and turns from north " +
        "to southwest. An archway leads into a dungeon to the southeast.");

    add_walls();
    add_floor();
    add_archway("southeast");
    add_c_passages("north", "southwest");
    add_ceiling();

    add_exit(CELLAR_DIR + "pass_1e4", "north",     0, 1);
    add_exit(CELLAR_DIR + "dung_1e1", "southeast", 0, 1);
    add_exit(CELLAR_DIR + "pass_1e2", "southwest", 0, 1);
}

