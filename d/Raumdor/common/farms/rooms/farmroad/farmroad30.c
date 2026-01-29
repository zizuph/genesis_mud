/* 
 * /d/Raumdor/common/farms/farmroad30.c
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
        "Drakmere. The Desolate Plains spread out all around you "+
        "on all sides. Low stunted trees dot the landscape.\n");
 
    add_exit(FARMROAD_DIR + "farmroad29","north");
/*
 *  add_exit(FARMROAD_DIR + "farmroad30","south");
 *
 *  Add connection to Royal Road. 
 */
    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "west", "east", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 27, 0}); 
}
