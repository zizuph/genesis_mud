/* 
 * /d/Raumdor/common/farms/farmroad03.c
 *
 * Ardent 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_road();
    set_items_mill();
    set_items_city();

    set_short("On the farm roads south of Drakmere");

    set_long("You are on an old worn road that runs northwest to the "+
        "city gates and straight south to the farms and the mill. All "+ 
        "around you, you see flat plains, fields and rolling hills. The "+
        "air is cold and stale, and you can almost feel the bleakness "+ 
        "that envelopes this place. The road is dirt in some places, and "+
        "made of cobblestone in other places. \n");

    add_exit(FARMROAD_DIR + "farmroad02","northwest");
    add_exit(FARMROAD_DIR + "farmroad04","south");

    set_no_exit_msg( ({"north", "northeast", "east", "southeast", 
            "southwest", "west", }),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 9, 0}); 
}
