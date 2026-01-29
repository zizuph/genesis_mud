/* 
 * /d/Raumdor/common/farms/farmroad14.c
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
        "path. You find yourself west of the main farm road and east "+
        "of the mill. Creaking sounds can be heard from the mill, but "+
        "the wings are not moving. In the distance you can see grain "+
        "fields and plains on all sides. Low stunted trees dot the "+
        "landscape. A fenced pasture with some sheep can be seen "+
        "across the bushes lining the path to the south.\n");

    add_item("road","It is an old and worn dirt road that has been filled "+
        "in with gravel to make it seem like it is in a better state. \n");

    add_item("bushes","Sprawling bushes line both sides of the road. "+ 
        "The ones to the south look bigger than the rest. Looking "+
        "closely you can see that someone has picked all the berries "+
        "this bush seems to have had. \n");

    add_exit(FARMROAD_DIR + "farmroad13","east");
    add_exit(FARMROAD_DIR + "farmroad15","west");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "north", "south", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({27, 21, 0}); 
}
