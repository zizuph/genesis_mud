/*
 * coded by Amelia 3/16/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include <ss_types.h>
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
        "vegetation and rocks. Directly to the north there is a " +
        "hedge of hemlock bushes.\n");
    add_item((({"floor", "forest floor"})),
        "The forest floor is fairly steep, and it is " +
        "difficult to walk here.\n");
    add_item("path",
        "The rugged path winds among large rocks and bushes.\n");
    add_item((({"hedge", "hemlock bushes", "bushes"})),
        "The dark green bushes of hemlock loom over the path " +
        "just to the north. "+ "@@entrance");
    set_search_places(({"bushes", "briars", "vegetation",
        "herbs", "trees", "evergreen trees"}));
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    reset_room();
    add_exit("trail1", "enter", "@@enter_bushes", 0, 1);
    add_exit("ne3", "northeast", 0, 2, 0);
    add_exit("ne1", "southwest", 0, 2, 0);
}

public string
entrance()
{
    object tp = this_player();

    if((tp->query_skill(SS_AWARENESS) > 10) &&
        (tp->query_skill(SS_LOC_SENSE) > 10))
    {
        return "Due to your keen senses, you notice an entrance " +
            "of sorts into the bushes.\n";
    }

    return "The bushes look very foreboding.\n";
}

public int
enter_bushes()
{
    object tp = this_player();

    if((tp->query_skill(SS_AWARENESS) > 10) &&
        (tp->query_skill(SS_LOC_SENSE) > 10))
    {
        return 0;
    }

    write("Enter what?\n");

    return 1;
}
