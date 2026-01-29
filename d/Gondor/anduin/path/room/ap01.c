/*
  A bridge over a stream near the Anduin in Ithilien.
*/
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";

#include "/d/Gondor/anduin/lib/and_defs.h"

public void
create_gondor()
{
    set_short("On a bridge over a small stream near a river");

    set_long(&long_desc());

    path_add_items();
    add_path_tells();
    mountain_add_items();

    set_tell_time(600);

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"island", "cair andros", "Cair Andros", "Andros",
        "long island"}), "A long island stretches lies in the middle "
        + "of the Anduin here. Known as Cair Andros, the island was "
        + "once fortified to protect Gondor against invasion. It is "
        + "abandoned at the moment, seemingly.\n"); 
    add_item(({"stream", "small stream"}), "A small stream flows under "
        + "the bridge here on its way to joining the Anduin.\n");
    add_item(({"forest", "forests", "ithilien", "Ithilien"}), "The "
        + "forests of Ithilien stand a just to the southeast.\n");
    add_item(({"bridge", "stone bridge", "small bridge", 
        "small stone bridge"}), "You are on a small stone bridge "
        + "crossing over a small stream as it empties into the Anduin "
        + "here. A path leads away from the bridge to the northwest "
        + "and southeast.\n");
    add_item(({"shadow", "shadows"}), "The small bridge casts the "
        + "stream below into shadow.\n");

    add_tell("The small stream gurgles cheerfully as it flows under "
        + "the bridge.\n");

    add_exit(AND_PATH + "ap02", "northwest", 0, 3, 0);
    add_exit("/d/Gondor/ithilien/road/rr10", "southeast", 0, 3, 0);
}

string
long_desc()
{
    return "On a stone bridge by a well-trodden path across a swamp near "
        + "the river Anduin." + sky_desc() + "the path and bridge, casting "
        + "shadows onto the small stream below. Swamps extend to the north as "
        + "far as the eye can see. To the southwest, a long island rises from "
        + "the river. The forests of Ithilien grow thickly to the "
        + "southeast.\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
        river_add_items();
}
