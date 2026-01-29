/*
 * Bridge central room
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
    add_exit("roomr1", "south");
    add_exit("roomr3", "north");

} /* create_room */

/*
 * Function name:        get_bridge_part
 * Description  :        return bridge part
 */
string 
get_bridge_part()
{
    return "central";    
} /* get_bridge_part */

/*
 * Function name:        get_lake_desc
 * Description  :        returns lake description. 
 */
string 
get_lake_desc()
{
    return "Leaning over the edge of the bridge, you hear more than see the " +
           "black waters of the lake below.\n";
} /* get_lake_desc */

/*
 * Function name:        get_down_room
 * Description  :        room under the bridge
 */
string 
get_down_room()
{
    return "roomub2";
} /* get_down_room */
