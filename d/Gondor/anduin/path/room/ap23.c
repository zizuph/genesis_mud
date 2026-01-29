/*
  A path along Nen Hithoel.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/anduin/lib/and_defs.h"

public void
create_gondor()
{
    set_short("A narrow path near a lake");

    set_long(&long_desc());

    path_add_items();
    add_path_tells();
    marsh_add_items();
    add_river_tells();

    drinkable();

    set_tell_time(600);

    set_no_exit_msg(({"west", "northwest"}), 
        "The hill is too steep in that direction.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil", "large hills"}), 
       "To the east, the hills of the Emyn Muil rise above the land. "
        + "To the east lies the hill Amon Lhaw, mirrored further south "
        + "across the lake by its twin, Amon Hen.\n");
    add_item(({"path", "narrow path"}), "The narrow path winds around "
        + "the eastern shore of the lake.\n");
    add_item(({"trees", "pine trees"}), "Pine trees crowsd the hills "
        + "and both shores of the lake.\n");
    add_item(({"island", "small island", "pointy island", "rocky island", 
        "tol brandir", "Tol Brandir", "tindrock", "Tindrock"}), "Far to "
        + "the south, you can make out a small, pointy island rising "
        + "out of the lake's southern end.\n");
    add_item(({"amon hen", "Amon Hen", "hill of sight", "Hill of Sight"}), 
        "The hill Amon Hen, the Hill of Sight of old Gondor, rises in "
        + "the distance over the eastern shores of Nen Hithoel.\n");  
    add_item(({"amon lhaw", "Amon Lhaw", "hill of hearing", 
        "Hill of Hearing"}), "The hill Amon Lhaw, the Hill of Hearing of "
        + "old Gondor, rises just to the southeast.\n");
    add_item(({"rauros", "falls", "Rauros", "falls of rauros",
        "falls of Rauros"}), "Though they are out of sight, you can hear "
        + "the distant droning roar as the waters of Nen Hithoel empty over "
        + "the falls to the south, reforming the Anduin as it flows toward "
        + "the distant sea.\n");
    add_item(({"lake", "placid lake", "nen hithoel", "Nen Hithoel", 
        "waters", "river", "anduin", "Anduin", "river anduin", "cool waters",
        "River Anduin", "south end", "southern end"}), "The waters of "
        + "the River Anduin pools here into the placid lake Nen Hithoel. "
        + "The cool waters are stopped by the bulk of Amon Hen and Amon "
        + "Lhaw, passing southward around either side of the island of "
        + "Tol Brandir before crashing down through the falls of Rauros.\n");


    add_tell("The faint droning sound of a great waterfall drifts over "
        + "the lake from the south.\n");

    set_drink_from(({"lake", "Nen Hithoel", "nen hithoel"}));

    add_exit(AND_PATH + "ap24", "northeast", 0, 3, 0);
    add_exit(AND_PATH + "ap22", "southeast", 0, 3, 0);
    add_exit("/w/serif/nen/nb02", "southwest", 0, 3, 1);
}

string
long_desc()
{
    return "On a narrow path on the eastern shore of Nen Hithoel." 
        + sky_desc() + "the path as it winds its way through the trees "
        + "along the placid lake. Furhter south, two large hills loom "
        + "at the end of the lake, where you can make out a small island "
        + "rising above the water.\n"; 
}

public void
drink_message(string from)
{
    write("You drink some water from the placid lake Nen Hithoel.\n"
        + "You feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some water from the placid lake Nen "
        + "Hithoel.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}

public void
init()
{
    ::init();
    init_drink();
}
