/* 
 * /d/Raumdor/common/blonks/blonks09.c
 * Blonks parents bedroom.
 * Ardent 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_blonks();

    set_short("The farmhouse main bedroom ");

    set_long("This is a small and cramped room. On your left "+
        "side a bed lines the wall and on the opposite side "+
        "is a closet.\n"); 

    add_item(({"door", "doors"}), "This is a solid wooden door. "+
        "It has been locked in place to keep it open.\n");

    add_item(({"bed", "beds"}),
        "The bed is made from a wooden frame and filled with straw. "+
        "Two blankets have been folded neatly and placed in one end. "+
        "The straw is flattened from many months of use.\n");

    add_item(({"blanket", "blankets"}), 
        "These coarse blankets are made from raw wool and should be good "+
        "for staying warm during the long cold nights.\n");

    add_item(({"closet"}), 
        "The raw wood used to make this closet resembles the stunted "+
        "trees you saw outside. It is worn down and splintered around "+
        "the sides. Dust covers the top. The hinges are completely "+
        "rusted and make it hard to open the closet. Inside you find "+
        "some old farm clothes.\n");

    add_item(({"clothes", "farm clothes"}), 
        "They are old and littered with holes.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(BLONKS_DIR + "blonks06","south");

    set_no_exit_msg( ({"northeast", "southeast", 
            "southwest", "northwest", "north", "east", "west"}),
        "The wooden walls prevent you from going in that direction. You "+
        "should exit through the door leading south instead.\n");
}

int *
query_coordinates()
{
    return ({25, 5, 0}); 
}
