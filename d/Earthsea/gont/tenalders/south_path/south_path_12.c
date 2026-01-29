/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/south_path/base_south_path";
#include <stdproperties.h>

public void
create_gloomy_forest()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    add_my_desc("The path continues west and northeast.\n");
    add_exit("south_path_11", "northeast");
    add_exit("south_path_13", "west");
}
