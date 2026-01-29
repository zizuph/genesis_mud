/* 
 * /d/Raumdor/common/farms/farmroad19.c
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
    
    set_short("Intersection of farmroad and two paths");

    set_long("Gravel crunches under your feet as you arrive at an "+
        "intersection. The main road continues north and south "+
        "while two smaller paths will take you east and west. "+
        "Gravel has been strewn over all the four roads, as "+
        "they seem to be used extensively. The gravel is not "+
        "as good as the cobblestones used closer to Drakmere, "+
        "but it does increase traversability for both those on "+
        "foot and those riding. A large official looking sign "+
        "has been planted next to the road.\n");  

    add_item(({"sign", "large sign", "large official sign", 
            "official sign"}), 
        " +--------------------------+ \n"+
        " | North - Drakmere         | \n"+   
        " | South - The Great Plains | \n"+
        " | West  - Cartwrights      | \n"+
        " | East  - Horraces         | \n"+
        " +--------------------------+ \n"+
        " |  |                    |  | \n"+
        " |  |                    |  | \n");

    add_exit(FARMROAD_DIR + "farmroad18","north");
    add_exit(FARMROAD_DIR + "farmroad22","south");
    add_exit(FARMROAD_DIR + "farmroad21","west");
    add_exit(FARMROAD_DIR + "farmroad20","east");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 9, 0}); 
}
