/*
 * /d/Gondor/morgul/cellar/dung_1e1.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
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
    set_room_type("gloomy dungeon");
    set_extra_long("There are two exits, an archway to the northwest " +
        "beyond which a dark tunnel is visible and an archway leading " +
        "down into the dark.");

    add_walls();
    add_floor();
    add_archway("northwest");
    add_down_archway();
    add_ceiling();

    add_exit(CELLAR_DIR + "pass_1e3", "northwest", 0, 1);
    add_exit(CELLAR_DIR + "torture", "down", 0, 1);
}

