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
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("A new trail");
    add_my_desc("A trail, which has been brutally hacked " +
        "through the forest, goes east and west here.\n");
    add_item((({"branches", "trail"})),
        "The narrow trail goes west and east through the forest, " +
        "and as you look at the green branches cast carelessly " +
        "to the side, it appears to have been made recently " +
        "in a hurry.\n");
    add_item((({"forest", "trees"})),
        "Tall pine and larch trees from the evergreen " +
        "forest surround you.\n");
    set_tell_time(90);
    add_tell("A cloud of pine smoke comes from the west.\n");
    add_tell("You have the feeling you are being watched.\n");
    add_exit("camp_1/karg_camp01", "west");
    add_exit("trail2","east");
}
