/* 
 * /d/Raumdor/common/farms/farmroad12.c
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

    set_short("On the gravel road between the farm road and the mill");
    
    set_long("Gravel crunches under your feet as you walk along the "+ 
        "path. You find yourself west of the main farm road, somewhat "+
        "east of the mill. Creaking sounds can be heard from the mill, "+
        "but the wings are not moving. In the distance you can see "+
        "grain fields and plains on all sides. Low stunted trees dot the"+
        " landscape.\n");

    add_exit(FARMS_DIR + "farmroad11","east",0,0);
    add_exit(FARMS_DIR + "farmroad13","west",0,0);

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "north", "south", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({33, 21, 0}); 
}
