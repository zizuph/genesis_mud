/* 
 * /d/Raumdor/common/farms/farmroad20.c
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
    
    set_short("On a path between the farmroad and Horraces farm");

    set_long("Walking along this path you are now between the main "+
        "farmroad to the west and the Horraces farm to the east. "+
        "You can hear and smell cows, and the tips of their heads "+
        "can just be spotted over the bushes to the southeast. "+
        "Curiously the strongest smell of cows seems to be comming "+
        "from the northeast. The mill is still visible though it is "+
        "now quite far to the northwest. Beyond the cows and the "+
        "farm, the plains and hills continue.\n"); 
 
    add_exit(HORRACES_DIR + "horraces01","east");
    add_exit(FARMROAD_DIR + "farmroad19","west");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "north", "south", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({40, 9, 0}); 
}
