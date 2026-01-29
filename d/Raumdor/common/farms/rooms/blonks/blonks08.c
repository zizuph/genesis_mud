/* 
 * /d/Raumdor/common/blonks/blonks08.c
 * Blonks kitchen pantry.
 * Ardent 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_blonks();

    set_short("The farmhouse kitchen pantry ");

    set_long("The scent of food wafts in through the west door. "+
        "A few boxes are stacked in the corner and some barrels "+
        "line the walls. \n"); 

    add_item(({"door", "doors"}), "This is a solid wooden door. "+
        "It has been locked in place to keep it open.\n");

    add_item(({"box", "boxes"}),
        "These boxes are made from wood. The wood is worn down and "+
        "tarnished. They are all empty.\n");

    add_item(({"barrel", "barrels"}), 
        "Lining the walls is a mix of wooden and ceramic barrels. The "+
        "wooden barrels are all empty. Some of the ceramic barrels "+
        "contain a little flour.\n");

    add_item(({"flour"}), 
        "Looking into one of the ceramic barrels you notice that it is "+
        "old and moldy.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(BLONKS_DIR + "blonks07","west");

    set_no_exit_msg( ({"northeast", "southeast", 
            "southwest", "northwest", "north", "east", "south"}),
        "The wooden walls prevent you from going in that direction. You "+
        "should exit through the door leading west instead.\n");
}

int *
query_coordinates()
{
    return ({29, 7, 0}); 
}
