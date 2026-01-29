/* 
 * /d/Raumdor/common/farms/farmroad06.c
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

    set_short("On the farm road north of the farms");

    set_long("You are on an old worn road that runs north to the city of "+
        "Drakmere and south to the farms and the mill. All around you, "+
        "you see flat plains, fields and rolling hills. "+
        "Off in the distance to the southwest you can see the Mill. On the "+
        "other side of the road you notice a farm. The air is cold and "+
        "stale, and you can almost feel the bleakness that envelopes this "+
        "place.\n");
 
    add_exit(FARMROAD_DIR + "farmroad05","north");
    add_exit(FARMROAD_DIR + "farmroad07","south");

    set_no_exit_msg( ({"northeast", "east", "southeast", "southwest",
            "west", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 15, 0}); 
}
