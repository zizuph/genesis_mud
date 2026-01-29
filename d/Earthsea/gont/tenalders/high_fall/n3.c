/*
 * coded by Amelia 3/16/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"

public void
create_forest_room()
{
    set_short("An ancient evergreen forest");
    set_long("Tall trees of the ancient evergreen forest " +
        "stand around you, scenting the crisp mountain air " +
        "with fresh pine. The forest floor is covered with dense " +
        "tangled briars and bushes. A rugged path, carpeted with " +
        "pine needles, ascends the mountain, winding among the " +
        "vegetation and rocks.\n");
    add_item((({"floor", "forest floor"})),
        "The forest floor is fairly steep, and it is " +
        "difficult to walk here.\n");
    add_item("path",
        "The rugged path winds among large rocks and bushes.\n");
    set_up_herbs(select_herb_files(FOREST_HERBS),
        FOREST_LOCATIONS, 3);
    reset_room();
    add_exit("n4", "northwest", 0, 2, 0);
    add_exit("n2", "southeast");
}
