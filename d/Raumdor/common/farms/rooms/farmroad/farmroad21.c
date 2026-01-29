/* 
 * /d/Raumdor/common/farms/farmroad21.c
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
    
    set_short("On a path between the farmroad and Cartwrights farm");

    set_long("Walking along this path you are now between the main "+
        "farmroad to the east and the Cartwrights farm to the west. "+
        "You can hear and smell sheep, but they must to be too "+
        "low to be seen over the bushes. You guess they are somewhere"+
        " to the nortwest. The mill is still visible though it is now "+
        "quite far to the northwest, somewhere beyond the sheep. The "+
        "plains and hills continue past the farmsouth blocking your "+
        "view to the southwest.\n"); 
 
    add_exit(CARTWRIGHTS_DIR + "cartwrights01","west");
    add_exit(FARMROAD_DIR + "farmroad19","east");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "north", "south", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({36, 9, 0}); 
}
