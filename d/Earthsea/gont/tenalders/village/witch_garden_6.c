/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's garden
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "garden_tells.h"
#include <macros.h>

public void
create_herb_room()
{
    int i;
    set_short("A garden");
    set_long("The path winds through what appears to " +
        "be a semi-cultivated, wild garden. Although some " +
        "plants are ranked in rows, others are allowed to " +
        "grow just as they wish. Vines, small trees, herbs " +
        "and bushes grow in rich profusion. " +
        "The path turns west here, blocked by a row " +
        "of bushes to the north. To the northeast " +
        "the path, veiled by foliage, bends around " +
        "a large oak tree.\n");
    add_item((({"bushes", "row of bushes", "purple fruit"})),
        "The briar bushes are covered with thorns and " +
        "some kind of small purple fruit.\n");
    add_item((({"tree", "oak tree"})),
        "A large oak tree stands at the northeast corner " +
        "of the garden.\n");
    add_item("plants",
        "Many types of plants grow here including " +
        "common garden plants and some which " +
        "have planted themselves from the wild.\n");
    add_item("vines",
        "The vines have some little green fruit on " +
        "them, possibly grapes.\n");
    add_item((({"fruit", "fruits"})),
        "Which fruit, the purple fruit or the red fruit?\n");
    add_item((({"red fruit", "red fruits", "green fruit"})),
        "Low to the ground some viney plants are planted in rows, " +
        "and red and unripe green round fruits weigh down their " +
        "vines.\n");
    add_item((({"herb", "herbs"})),
        "Green and dark purple herbs scent the air.\n");
    add_item("path",
        "A narrow grass-covered path winds through " +
        "the garden among the vegetation.\n");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_herb_file("/d/Earthsea/herbs/herb_files/oakmoss");
    add_herb_file("/d/Earthsea/herbs/herb_files/tomato");
    set_tell_time(120);
    add_exit("witch_garden_8", "northeast");
    add_exit("witch_garden_7", "west");
    add_exit("witch_garden_4", "south");
    reset_room();

    for(i = 0; i < 4; i++)
    {
        add_tell(TELLS[random(sizeof(TELLS))]);
    }
}

public int
climb(string str)
{
    object tp = this_player();

    if(str == "tree" || str == "oak tree")
    {
        write("Grabbing ahold of some low branches, you " +
            "climb the oak tree.\n");
        tell_room(this_object(), QCTNAME(tp) + " grabs some low " +
            "branches and climbs up the big oak tree.\n", ({ tp }));
        tp->move_living("M",
            "/d/Earthsea/gont/tenalders/village/oak_tree", 1);
        tell_room(environment(tp), QCTNAME(tp) + " enters.\n", ({ tp }));
        return 1;
    }

    return notify_fail("Climb what?\n");
}

public void
init()
{
    ::init();
    add_action(climb, "climb");
}
