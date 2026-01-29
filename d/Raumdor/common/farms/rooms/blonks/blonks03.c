/* 
 * /d/Raumdor/common/blonks/blonks03.c
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
    set_items_blonks();

    set_short("In the center of the Blonks' courtyard ");

    set_long("Walking into the center of the courtyard you get a good "+
        "overview of the farm. Heading north will take you to the "+
        "stable and the entrance to the farmhouse you are standing "+
        "next to. Walking south will take you into the pasture.\n"); 

    add_item(({"road", "courtyard"}), "It is old and worn, made of "+
        "dirt and with tracks from the farmers carts and the horses "+
        "all over it. \n");

    add_exit(BLONKS_DIR + "blonks02","west");
    add_exit(BLONKS_DIR + "blonks04","north");
    add_exit(BLONKS_DIR + "blonks19","south");

    set_no_exit_msg( ({"southwest", "northwest"}),
        "There are bushes along the side of the path " +
        "preventing you from going in that direction!\n");
    set_no_exit_msg( ({"northeast", "southeast", "east"}),
        "The farms house prevents you from going in that direction!\n");
}

int *
query_coordinates()
{
    return ({19, 9, 0}); 
}
