/* 
 * /d/Raumdor/common/blonks/blonks06.c
 * Main living room.
 * Ardent 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_blonks();

    set_short("The main living room of the farmhouse ");

    set_long("This spacious room seems somewhat empty. In one "+
        "corner you can see some childrens toys and in another "+
        "there are two rocking chairs. This could be a living "+
        "room for when the Blonks are not working, which seems "+
        "to happen very rarely. There are doors leading in all "+
        "directions. Towards the west you can see the door "+
        "leading out of the farmhouse. In the east direction "+
        "the scent of food is wafting through the doorway.\n"); 

    add_item(({"door", "doors"}), "These are solid wooden doors. "+
        "They have been locked in place to keep them open.\n");

    add_item(({"chair", "chairs", "rocking chair", "rocking chairs"}),
        "These two rocking chairs are made of the same kind of wood "+
        "the house is made of. Dark and slightly twisted as it is, "+
        "the chairs themselves still look very comfortable. The "+
        "upholstery on the chairs looks old and worn from countless "+
        "hours of the family being gathered and watching the children "+
        "play with their toys.\n");

    add_item(({"toys", "toy", "childrens toys", "child toys"}), 
        "There are several wooden blocks, a spindle top and a "+
        "stuffed cloth doll. All of them well used and worn out.\n"); 

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(BLONKS_DIR + "blonks04","west");
    add_exit(BLONKS_DIR + "blonks07","east");
    add_exit(BLONKS_DIR + "blonks09","north");
    add_exit(BLONKS_DIR + "blonks12","south");

    set_no_exit_msg( ({"northeast", "southeast", 
            "southwest", "northwest"}),
        "The wooden walls prevent you from going in that direction.\n");
}

int *
query_coordinates()
{
    return ({25, 7, 0}); 
}
