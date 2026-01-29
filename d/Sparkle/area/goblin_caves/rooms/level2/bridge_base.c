/*
 * Bridge room base room
 * Boreaulam, Nov 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

string get_bridge_part();
string get_lake_desc();
string get_down_room();

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Rope bridge");
    set_long("You are currently standing on the " + get_bridge_part() + 
        " part of a flimsy rope bridge which stretches across a wide " +
        "underground lake which fills the middle of an enormous cavern. " +
        "Far away, you can see the sputtering light of dozens of torches " +
        "which appear to be hanging on the cavern walls, their light dancing " +
        "out across the lake, twinkling on top of the tiny, rippling waves. " +
        "You notice several thick ropes which hang down limply from the " +
        "bridge, dipping into the black water below. Following the bridge " +
        "to either the north or the south will bring you back to the rocky " +
        "shore of the lake." +
             "\n\n");
    
    add_item(({"bridge", "rope bridge"}),
             "This is a very simple rope bridge, constructed from thick " +
             "ropes tied around solid wooden planks. There are ropes on " +
             "either side of the bridge for you to hold onto as you cross, " +
             "including some that occasionally hang down into the black " +
             "water of the lake below, allowing someone in the water to " +
             "climb back up.\n");
    add_item(({"rope", "ropes", "hemp rope", "hemp ropes"}),
             "These thick ropes, which appear to be made of hemp, are " +
             "quite strong. Most of the ropes run across the length of the " +
             "lake, forming the bridge and handholds, but a few ropes " +
             "hang down towards the black water below, allowing someone to " +
             "climb either up or down.\n");
    add_item(({"plank", "planks", "wooden plank", "wooden planks"}),
             "Thick and solid, these wooden planks form the base of the " +
             "bridge beneath your feet.\n");
    add_item(({"cavern", "cave", "enormous cavern"}),
             "You are in the middle of an enormous cavern, far below the " +
             "mountains above. However, you cannot really see the walls or " +
             "ceiling while you are in the middle of the lake.\n");
    add_item(({"torch", "torches"}),
             "You can spot dozens of torches, far away, circling the lake " +
             "as they have been mounted on the walls of the cavern.\n");
    add_item(({"wave", "waves", "ripple", "ripples"}),
             "Out across the lake, you can see the light from the torches " +
             "dancing and twinkling on the gentle waves which ripple as " +
             "they rise and fall.\n");
    add_item(({"wall", "walls"}),
             "You cannot see the walls of the cavern clearly, but the light " +
             "from the torches outlines the edge of the cavern which " +
             "circles around you.\n");
    add_item(({"up", "ceiling", "shadows", "shadow"}),
             "The ceiling above is nothing more than a mass of jagged " +
             "shadows, as the light is not bright enough here to make out " +
             "any details.\n");
    add_item(({"shore", "lakeshore", "edge", "lake edge"}),
             "Off in the distance, you can see the rippling waves of the " +
             "lake gently brushing up against a rocky shore.\n");
    add_item(({"water", "lake", "cave lake", "waters", "basin", "black water",
                "surface"}),
             get_lake_desc());

    add_cmd_item( "down",
                  "climb", 
                  "@@climb_down");
    
} /* create_room */

/*
 * Function name:        get_bridge_part
 * Description  :        blank function to override to return part of bridge
 */
string 
get_bridge_part()
{
    return "wrong bridge part";
} /* get_bridge_part */

/*
 * Function name:        get_lake_desc
 * Description  :        blank function to override to return lake description
 */
string 
get_lake_desc()
{
    return "wrong lake desc";
} /* get_lake_desc */

/*
 * Function name:        climb down
 * Description  :        climb down the bridge
 */
string
climb_down()
{
    tell_room(this_object(), QCTNAME(this_player()) + " climbs down.\n");
    write("Grasping a solid length of rope in your hands, you climb down " +
        "towards the black waters of the lake below.\n\n");
    this_player()->move_living("M", ROOMS_DIR + "level2/" + get_down_room(), 1);

    return "";
} /* climb_down */

/*
 * Function name:        get_down_room
 * Description  :        blank function to override to return down bridge room
 */
string
get_down_room()
{
    return "under_bridge_base";
} /* get_down_room */

