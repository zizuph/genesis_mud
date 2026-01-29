/*
 * /d/Gondor/morgul/cellar/dung_1e5.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 18-Oct-1995
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

public string  ladder();

public void
create_morgul_cellar_room()
{
    object  door;

    set_level(1);
    set_room_type("gloomy dungeon");
    set_extra_long("There is only one exit, a flight of stairs going "
      + "down.");

    add_walls("@@ladder@@");
    add_floor();
    add_down_archway();

    add_exit(CELLAR_DIR + "pass_2e3", "down", 0, 1, 1);

    door = clone_object(MORGUL_DIR + "city/doors/cellar_down");
    door->move(TO);

    reset_room();
}

public string
ladder()
{
    if (objectp(present("ladder")))
        return "There is a ladder leaning against the north wall. \n";
    return "";
}

public void
reset_room()
{
    object  ladder;

    if (!objectp(ladder = present("ladder")))
    {
	ladder = clone_object(OBJ_DIR + "ladder");
	ladder->move(TO);
    }
    ladder->set_no_show_composite(1);
}

