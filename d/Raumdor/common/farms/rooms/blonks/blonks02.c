/* 
 * /d/Raumdor/common/blonks/blonks02.c
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
    set_items_blonks();

    set_short("On the western side of the main courtyard ");

    set_long("You are on a worn track just inside the farm. Here the path "+
        "widens and becomes a courtyard that seems to be the center of the "+
        "farm. Every day the horses are lead from the stable in the "+ 
        "northeast, through the courtyard and towards the southeast into the "+
        "pasture. The main farmhouse can be seen across the courtyard. "+
        "In the distance to the southwest you can see the Mill. \n");

    add_item("road","It is old and worn, made of dirt and with tracks "+
    "from the farmers carts all over it. \n");

    add_exit(BLONKS_DIR + "blonks01","west");
    add_exit(BLONKS_DIR + "blonks04","northeast");
    add_exit(BLONKS_DIR + "blonks03","east");
    add_exit(BLONKS_DIR + "blonks19","southeast");

    set_no_exit_msg( ({"south", "southwest", "north", "northwest"}),
        "There are bushes along the side of the path " +
        "preventing you from going in that direction!\n");
}

int *
query_coordinates()
{
    return ({19, 9, 0}); 
}
