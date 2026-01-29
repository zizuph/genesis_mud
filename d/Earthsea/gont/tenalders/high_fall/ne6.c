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
    set_short("By a waterfall");
    set_long("The evergreen forest opens onto a view of " +
        "a vast waterfall, which is opposite you across a " +
        "large river. A suspended rope bridge crosses the " +
        "ravine. You hear the roar of rushing white water, " +
        "swirling far below you.\n");
    add_item((({"floor", "forest floor"})),
        "The forest floor is fairly steep, and it is " +
        "difficult to walk here.\n");
    add_item("path",
        "The rugged path winds among large rocks and bushes.\n");
    add_item((({"bridge", "rope bridge"})),
        "The rope bridge appears to be rotten from age and use. You " +
        "do not feel it would be wise to step out upon it.\n");
    add_item("waterfall", "A vast roaring waterfall crashes " +
        "down the cliff across the ravine to the northeast.\n");
    add_item("river", "Far below a river swirls rapidly from " +
        "the source of the waterfall.\n");
    add_item("ravine", "A vast chasm extends to the east from " +
        "this ledge.\n");
    set_search_places(({"bushes", "briars", "vegetation",
        "herbs", "trees", "evergreen trees"}));
    set_up_herbs(select_herb_files(FOREST_HERBS),
        FOREST_LOCATIONS, 3);
    reset_room();
    add_exit("ne5", "southwest", 0,2,0);
    add_exit("bridge1", "east");
}
