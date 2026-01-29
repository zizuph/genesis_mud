/* 
 * /d/Raumdor/common/farms/farmroad10.c
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

    set_short("Along the main farm road between the farms");

    set_long("You are on the main road in the northern part of the farms. "+
        "Surrounding you are the farms that feed the city of Drakmere. "+
        "The scent of farm is faint out here on the road. East of the "+ 
        "road you can see a pasture with a few horses. Further away you "+
        "can see grain fields and plains on all sides. Low stunted trees "+
        "dot the landscape. To the west a dirt track leads towards the "+
        "Mill. The air is calm here.\n");
 
    add_exit(FARMROAD_DIR + "farmroad09","north");
    add_exit(FARMROAD_DIR + "farmroad11","west");
    add_exit(FARMROAD_DIR + "farmroad16","south");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "east", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 21, 0}); 
}
