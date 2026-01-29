/* 
 * /d/Raumdor/common/farms/farmroad08.c
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

    set_short("East of the main farm road towards the Blonks Farm");

    set_long("You are on a worn track between the main road and a farm. "+
        "The scent of farm is whiffing about your nose. Towards the east "+
        "you can make out a farmhouse. Surrounding the farmhouse is a "+
        "pasture with a few horses. All around you, you see flat plains "+
        "and fields. Just north of the farmhouse you notice a barn. Low "+
        "stunted trees dot the landscape. In the distance to the "+
        "southwest you can see the Mill. The air is chill and calm here.\n");

    add_exit(FARMROAD_DIR + "farmroad07","west");
    add_exit(BLONKS_DIR + "blonks01","east");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "north", "south", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({40, 17, 0}); 
}
