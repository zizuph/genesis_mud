/* 
 * /d/Raumdor/common/blonks/blonks05.c
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

    set_short("Inside the entrance room of the farmhouse ");

    set_long("This is a small cramped room. It connects the outer "+
        "door with an inner door. This room is where the farmers "+
        "leave their jackets and dirty footwear. Apart from the "+
        "shoe shelves along the walls there is nothing of interest "+
        "here. Light streams in from the open door and keeps the "+
        "area well lit.\n"); 

    add_item(({"road", "courtyard"}), "It can barely bee seen out "+
        "through the doorway. It is old and worn, made of dirt and "+
        "with tracks from the farmers carts and the horses all "+
        "over it. \n");

    add_item(({"door", "doors"}), "These are solid wooden doors. "+
        "They have been locked in place to keep them open.\n");

    add_item(({"shelf", "shoe shelf", "shelves", "shoe shelves",
            "shoes", "boots", "footwear"}),
        "A few dusty shoes and boots can be seen on the shelves. "+
        "They are all old, worn and worthless.\n");

    add_item(({"jackets", "jacket"}), "There are five hooks mounted "+
        "on the wall. One one of them you see an old woolen jacket. "+
        "The holes in it suggests it is only used in emergencies.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(BLONKS_DIR + "blonks04","west");
    add_exit(BLONKS_DIR + "blonks06","east");

    set_no_exit_msg( ({"north", "northeast", "southeast", 
            "south", "southwest", "northwest"}),
        "The wooden walls prevent you from going in that direction.\n");
}

int *
query_coordinates()
{
    return ({23, 7, 0}); 
}
