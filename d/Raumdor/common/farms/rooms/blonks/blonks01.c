/* 
 * /d/Raumdor/common/blonks/blonks01.c
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

    set_short("At the entrance of the Blonks Farm");

    set_long("You are on a worn track between the main road and a farm. "+
        "North of here you can see a stable. Judging by the smell wafting out "+
        "through the open doors, there are horses inside. Towards "+
        "the east you can see a courtyard spreading out in front of a "+
        "farmhouse. The house is a low well built structure made of wooden "+
        "timber. The front door looks solid and there are no visible windows. "+
        "South of the farmhouse is a pasture with a few horses. In the "+
        "distance to the southwest you can see the Mill. \n");

    add_item("road","It is old and worn, made of dirt and with tracks "+
    "from the farmers carts all over it. \n");

    add_exit(FARMS_DIR + "farmroad08","west");
    add_exit(BLONKS_DIR + "blonks02","east",0,0,0);

    set_no_exit_msg( ({"northeast", "southeast", "south", "southwest",
            "north", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}

int *
query_coordinates()
{
    return ({17, 9, 0}); 
}
