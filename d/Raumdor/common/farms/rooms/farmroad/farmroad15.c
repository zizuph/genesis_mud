/* 
 * /d/Raumdor/common/farms/farmroad15.c
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

    set_short("On the gravel path just outside the mill");

    set_long("Gravel crunches under your feet as you walk along the "+ 
        "path. In front of you looms the imposing mill. It is built "+
        "from big lumber planks and seems to be in good condition. "+
        "There are windows at the top of the main building. Creaking "+
        "sounds can be heard from the mill, but the wings are not "+
        "moving. In the distance you can see grain fields and plains "+
        "on all sides. Low stunted trees dot the landscape. A fenced "+
        "pasture with some sheep can be seen across the bushes lining "+
        "the path to the south.\n");

    add_item("windows","They are too high up to see clearly from here. \n");

    add_item(({"fenced pasture", "pasture"}), "A fenced pasture with "+
        "some sheep can be seen across the bushes lining the path to "+
        "the south.\n");

    add_item("bushes","Sprawling bushes line both sides of the road. "+ 
        "The ones to the south look bigger than the rest. Looking "+
        "closely you can see that someone has picked all the berries "+
        "this bush once had. \n");

    add_item(({"wing", "wings"}), "The wings on the mill are the length "+
        "of 3 horses. You wonder how they managed to mount these immense "+
        "pieces so high in the air.\n"); 

    add_exit(FARMROAD_DIR + "farmroad14","east");
    add_exit(FARMROAD_DIR + "mill","north");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "west", "south", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({24, 21, 0}); 
}
