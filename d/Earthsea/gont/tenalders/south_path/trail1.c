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
    add_my_desc("A new trail has been hacked through " +
        "the forest to the west.\n");
    add_item((({"trail", "new trail"})),
        "The trail looks new judging from the green branches that " +
        "lay strewn carelessly about.\n");
    set_tell_time(130);
    add_tell("A cloud of pine smoke comes from the west.\n");
    add_tell("You have the feeling you are being watched.\n");
    add_exit("trail2", "west");
    add_exit("bushes", "east");
}
