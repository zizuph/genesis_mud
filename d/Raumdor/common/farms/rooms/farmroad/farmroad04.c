/* 
 * /d/Raumdor/common/farms/farmroad04.c
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

    set_long("You are on an old worn road that runs north to the "+
        "city of Drakmere and south to the farms and the mill. All around "+
        "you, you see flat plains, fields and rolling hills. The air is cold "+
        "and stale, and you can almost feel the bleakness that envelopes this "+ 
        "place. The road is dirt in some places, and made of cobblestone in "+ 
        "other places. \n");

    add_exit(FARMROAD_DIR + "farmroad03","north");
    add_exit(FARMROAD_DIR + "farmroad05","south");

    set_no_exit_msg( ({"northeast", "east", "southeast", "southwest",
            "west", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 11, 0}); 
}
