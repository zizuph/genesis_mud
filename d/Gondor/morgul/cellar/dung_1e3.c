/*
 * /d/Gondor/morgul/cellar/dung_1e3.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 19-Oct-1995
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

public void    reset_room();

static object  olog;

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("gloomy dungeon");
    set_extra_long("An archway is leading to the northwest; beyond it a "
      + "dark tunnel is visible. Another arch breaks through the eastern wall "
      + "leading into a dark cell. Just in front of you, a flight of stairs "
      + "is leading down into another dungeon.");

    add_item(({"east","east wall","east arch","eastern wall"}),
        "A narrow arch cuts through the eastern wall to lead into a dark " +
        "cell which radiates a rather unpleasant scent.\n");

    add_walls();
    add_floor();
    add_archway("northwest");
    add_archway("east");
    add_down_archway();
    add_ceiling();

    add_exit(CELLAR_DIR + "pass_1e5", "northwest", "@@check_exit@@", 1);
    add_exit(CELLAR_DIR + "tuvale", "east", "@@check_exit@@", 1);
    add_exit(CELLAR_DIR + "dung_2e3", "down",      "@@block_exit@@", 1);

    reset_room();
}

public void
reset_room()
{
    if (objectp(olog))
        return;

    olog = clone_object(MORGUL_DIR + "npc/ithil_olog");
    olog->arm_me();
    olog->move_living("down", TO);
}

