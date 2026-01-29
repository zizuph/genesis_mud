/* 
 * /d/Raumdor/common/blonks/blonks04.c
 *
 * Ardent 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_blonks();

    set_short("At the entrance of the stable and the farmhouse ");

    set_long("The stable is a solid building made of large timbers. "+
        "It is unpainted but kept in good repair. This is clearly "+
        "an important building to the farmers. The gates have been "+
        "left wide open. The door to the farmhouse is also open if "+
        "you want to head inside.\n"); 

    add_item(({"road", "courtyard"}), "It is old and worn, made of "+
        "dirt and with tracks from the farmers carts and the horses "+
        "all over it. \n");

    add_item(({"door", "doors"}), "This is a solid wooden door. It "+
        "has been locked in place to keep it open.\n");

    add_item(({"gate", "gates"}), "This is a large wooden gate. Both "+
        "sides have been locked down and cannot be moved.\n"); 

    add_item(({"stable", "stables"}), "The stable is a solid "+
        "building made of large timbers. It is unpainted but "+
        "kept in good repair. This is clearly an important "+
        "building to the farmers. But you already knew that?\n");

    add_exit(BLONKS_DIR + "blonks05","east");
    add_exit(BLONKS_DIR + "blonks15","north");
    add_exit(BLONKS_DIR + "blonks03","south");
    add_exit(BLONKS_DIR + "blonks02","southwest");

    set_no_exit_msg( ({"west", "northwest"}),
        "There are bushes along the side of the path " +
        "preventing you from going in that direction!\n");
    set_no_exit_msg( ({"northeast", "southeast"}),
        "The farms house prevents you from going in that direction!\n");
}

int *
query_coordinates()
{
    return ({21, 7, 0}); 
}
