/* 
 * /d/Raumdor/common/farms/farmroad26.c
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
    
    set_short("Along the main farm road south of the farms");

    set_long("You are on the main road south of the farms. "+
        "To the north you can see the farms that feed the city of "+
        "Drakmere. The scent of farm is faint out here on the road."+
        " Pastures and farms line both sides of the road. "+
        "Further away you can see grain fields and plains on all "+
        "sides. Low stunted trees dot the landscape.\n");
 
    add_exit(FARMROAD_DIR + "farmroad25","north");
    add_exit(FARMROAD_DIR + "farmroad27","south");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "west", "east", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 19, 0}); 
}
