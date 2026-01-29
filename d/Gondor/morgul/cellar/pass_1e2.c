/*
 * /d/Gondor/morgul/cellar/pass_1e1.c
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
    set_extra_long("The tunnel makes a bend here and turns from northeast "
      + "to west. Dark archways are leading into dimly lit dungeons "
      + "to the northwest and to the south.");

    add_walls();
    add_floor();
    add_c_passages("northeast", "west");
    add_ceiling();
    add_archways("northwest", "south");

    add_exit(CELLAR_DIR + "pass_1e3",     "northeast", 0, 1);
    add_exit(CELLAR_DIR + "potion_shop",  "south",     0, 1);
    add_exit(CELLAR_DIR + "pass_1e1",     "west",      0, 1);
    add_exit(CELLAR_DIR + "herb_shop",    "northwest", 0, 1);
}

