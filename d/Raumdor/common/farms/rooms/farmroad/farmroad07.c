/* 
 * /d/Raumdor/common/farms/farmroad07.c
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

    set_short("On the farm road near the north end of the farms");

    set_long("You are on an old worn road that runs north to the city of "+
        "Drakmere and south to the farms and the mill. On the eastern side "+
        "of the road you notice a worn track leading east towards a farm. A"+
        " sign has been planted next to the track. All around you, you see "+
        "flat plains and fields. Towards the north there are rolling hills "+
        "that block the view. Nearby to the southwest you can see the Mill."+
        " The air is chill and calm here. The road is made of dirt and "+
        "shows signs of the farms all around it. \n");

    add_item("sign","+------------------+ \n"+ 
                    "|   Blonks Farm    | \n"+
                    "+------------------+ \n"+
                    "         ||          \n"+
                    "         ||          \n"+
                    "         ||          \n"+
                    "         ||          \n");

    add_item(({"farm", "farms"}), "There is a farm to the east. You can "+
        "also see farms in the distance southwest and southeast of here.\n");

    add_exit(FARMROAD_DIR + "farmroad06","north");
    add_exit(FARMROAD_DIR + "farmroad08","east");
    add_exit(FARMROAD_DIR + "farmroad09","south");

    set_no_exit_msg( ({"northeast", "southeast", "southwest",
            "west", "northwest"}),
        "There are bushes along the side of the road " +
        "preventing you from going in that direction!\n");
}


int *
query_coordinates()
{
    return ({38, 17, 0}); 
}
