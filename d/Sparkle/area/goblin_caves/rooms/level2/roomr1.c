/*
 * Bridge south room
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
    add_exit("roomh3", "south");
    add_exit("roomr2", "north");

} /* create_room */

/*
 * Function name:        get_bridge_part
 * Description  :        return bridge part
 */
string 
get_bridge_part()
{
    return "southern";    
} /* get_bridge_part */

/*
 * Function name:        get_lake_desc
 * Description  :        returns lake description. Also it is the first 
 *                       warning about spider
 */
string 
get_lake_desc()
{
    return "Leaning over the edge of the bridge, you hear more than see the " +
           "black waters of the lake below. You do notice thick strands of " +
           "spider web wrapped around the ropes below you, and you cannot " +
           "help but wonder just how big a spider would need to be to spin " +
           "a web of that size.\n";
} /* get_lake_desc */

/*
 * Function name:        get_down_room
 * Description  :        room under the bridge
 */
string 
get_down_room()
{
    return "roomub1";
} /* get_down_room */

/*
 * Function name:        climb_down
 * Description  :        First warns about spider. Second climb will 
 *                       move under the bridge
 */
string
climb_down()
{
    string prop = "_goblin_caves_spider_warn";
    if(!this_player()->query_prop(prop))
    {
    this_player()->add_prop(prop, 1);
        return "You grasp the rope and start to climb down the side of " +
            "the bridge, but you quickly find yourself almost trapped " +
            "in the middle of a spider web. The thick, heavy strands of " +
            "webbing are extremely sticky, and deciding that now is not " +
            "the best time to provide some spider a juicy meal, you climb " +
            "back up to the bridge.\n";
    }
    if(this_player()->query_prop(prop) == 1)
    {
        if(this_player()->query_stat(SS_DIS) < 150)
            return "You brace yourself and grasp the rope in an effort to " +
                "climb down into the spider web below the bridge, but you " +
                "cannot seem to gather enough courage.\n";
        this_player()->add_prop(prop, 2);
        return "You pause just a moment before climbing down, with a dread " +
            "feeling that almost certain death would await you below. Are " +
            "you certain you want to go down here?\n";
    }

    write_file("/d/Sparkle/area/goblin_caves/log/spider_entered",
         ctime(time()) + " " + this_player()->query_name() + 
         " climbed down to spider.\n");

    return ::climb_down();
} /* climb_down */
