/*
 * /d/Gondor/morgul/cellar/dung_1e1.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 19-Oct-1995
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

public void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("gloomy dungeon");
    set_extra_long("There are two exits, an archway to the southwest " +
        "leading to a dark tunnel, and a second archway is leading " +
        "east into a dungeon that is lit by the light of a fire.");

    add_walls();
    add_floor();
    add_archways("southwest", "east", "The flickering light of a " +
                 "fire is shining through the archway to the east.");
    add_ceiling();

    add_exit(CELLAR_DIR + "pass_1e5", "southwest", check_exit, 1);
    add_exit(CELLAR_DIR + "wsmithy",  "east",      check_exit, 1);
}

