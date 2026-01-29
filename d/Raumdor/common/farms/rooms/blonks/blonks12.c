/* 
 * /d/Raumdor/common/blonks/blonks12.c
 * Blonks childrens bedroom.
 * Ardent 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_blonks();

    set_short("A bedroom in the farm house ");

    set_long("This is a small and cramped room. Several beds "+
        "line the walls. A small closet is leaning against the wall "+
        "in the corner.\n"); 

    add_item(({"door", "doors"}), "This is a solid wooden door. "+
        "It has been locked in place to keep it open.\n");

    add_item(({"bed", "beds"}),
        "These beds are made from a wooden frame and filled with straw. "+
        "A blanket has been folded neatly and placed in one end of each "+
        "bed. The straw is flattened from many months of use.\n");

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
        "They are old and littered with holes. Just like everything "+
        "else on the farm.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(BLONKS_DIR + "blonks06","north");

    set_no_exit_msg( ({"northeast", "southeast", 
            "southwest", "northwest", "south", "east", "west"}),
        "The wooden walls prevent you from going in that direction. You "+
        "should exit through the door leading north instead.\n");
}

int *
query_coordinates()
{
    return ({25, 9, 0}); 
}
