/* 
 * /d/Raumdor/common/farms/farmroad02.c
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
        "city gates. All around you, you see flat plains, fields and "+
        "rolling hills. The air is cold and stale, and you can almost "+
        "feel the bleakness that envelopes this place. The road is "+
        "dirt in some places, and made of cobblestone in other "+
        "places.\n");
    
    add_exit(FARMROAD_DIR + "farmroad01","northwest");
    add_exit(FARMROAD_DIR + "farmroad03","southeast");

    set_no_exit_msg( ({"north", "northeast", "east", "south", 
            "southwest", "west", }),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({36, 7}); 
}
