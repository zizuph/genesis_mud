/*
 * Bridge north room
 * Boreaulam, Dec 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BRIDGE_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();
    add_exit("roomr2", "south");
    add_exit("roomb3", "north");

} /* create_room */

/*
 * Function name:        get_bridge_part
 * Description  :        return bridge part
 */
string 
get_bridge_part()
{
    return "northern";    
} /* get_bridge_part */

/*
 * Function name:        get_lake_desc
 * Description  :        returns lake description. 
 */
string 
get_lake_desc()
{
    return "Leaning over the edge of the bridge, you hear more than see the " +
           "black waters of the lake below. There appears to be some " +
           "movement in the darkness however, perhaps there is something " +
           "floating on the water?\n";
} /* get_lake_desc */

/*
 * Function name:        get_down_room
 * Description  :        room under the bridge
 */
string 
get_down_room()
{
    return "roomub3";
} /* get_down_room */
