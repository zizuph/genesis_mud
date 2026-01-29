/*
 * coded by Amelia 6/1/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/south_path/base_south_path";
#include <stdproperties.h>

public void
create_gloomy_forest()
{
    set_short("A trail through the forest");
    add_my_desc("A new trail goes east and west.\n");
    add_item((({"trail", "new trail"})),
        "It looks like the new trail was brutally hacked through " +
        "the forest as you look around at the wreckage of branches.\n");
    add_item((({"branches", "trail"})),
        "The narrow trail goes west/east through the forest " +
        "and as you look at the green branches cast carelessly " +
        "to the side, it appears to have been made recently " +
        "in a hurry.\n");
    add_item((({"forest", "trees"})),
        "Tall pine and larch trees from the evergreen " +
        "forest surround you.\n");
    set_tell_time(200);
    add_tell("A cloud of pine smoke comes from the west.\n");
    add_tell("You have the feeling you are being watched.\n");
    add_exit("trail3", "west");
    add_exit("trail1", "east");
}
