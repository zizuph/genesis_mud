/*
 * coded by Amelia 6/1/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <stdproperties.h>
#include <ss_types.h>

private int trail_open = 0;

public void
create_herb_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("In the bushes");
    set_long("You find yourself in a small area enclosed " +
        "by thick cedar bushes. Branches from pine trees arch overhead, " +
        "making this area appear like the entrance to a cave. " +
        "@@trail");
    add_item((({"brush", "heap", "huge heap of brush" })),
        "Someone has cut down branches from the bushes and trees " +
        "and stacked them in a huge heap just to the west.\n");
    add_item((({"forest", "trees", "bushes" })),
        "You are surrounded by the dense foliage of cedar bushes, and " +
        "overhanging boughs from the dense pine forest make this " +
        "almost like the entrance to a cave.\n");
    add_item((({"trail", "faint trail"})), "@@trail_item");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_5", "out");
    add_prop(OBJ_S_SEARCH_FUN, "find_trail");
    add_prop(OBJ_I_SEARCH_TIME, 3);
}

public void
reset_room()
{
    ::reset_room();
    trail_open = 0;
    remove_exit("west");
}

public string
trail()
{
    if(trail_open)
    {
        return "You see a that a small trail has opened to the west.\n";
    }

    return "Just to the west there is a huge heap of brush, " +
        "which blocks movement in that direction.\n";
}

public string
trail_item()
{
    if(trail_open)
    {
        return "You see a small trail open through the brush to " +
            "the west.\n";
    }

    return "You do not see a trail here.\n";
}

public string
find_trail(object player, string str)
{
    if(str == "brush" || str == "heap" || 
        str == "huge heap of brush" || str == "heap of brush")
    {
        if(player->query_skill(SS_AWARENESS) > 10 && (!trail_open))
        {
            trail_open = 1;
            add_exit("/d/Earthsea/gont/tenalders/south_path/trail1", "west");
            return "You tear away some of the brush, revealing a trail " +
                "to the west.\n";
        } else if(trail_open) {
            return "The brush is torn aside, revealing a trail to the " +
                "west.\n";
        }

        return "You find nothing of interest in the brush.\n";
    }

    return herb_search(player, str);
}
