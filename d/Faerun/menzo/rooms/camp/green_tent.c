/*
*
*  Clyptas September 2017
*
*/



#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
 
inherit "std/room";

public void
create_room()

{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short ("Inside a small green tent.");

    set_long("The tent is neat and tidy, in a military fashion. There are " +
         "bedrolls tied and stacked neatly on one side, while weapons and " +
         "armours hang from racks placed in the back of the tent.\n");
    
    add_item(({"bedrolls"}),
        "Tidy rolls of blankets and pillows line the side of the tent. " +
        "Stacked in an orderly fashion.\n");
    
    add_item(({"floor"}),
        "The floor of the tent is clean. Wood planks are laid out to keep " +
        "the area clean and the sweet smell of cedar from the planks fills " +
        "your nostrils.\n");
    
    add_item(({"planks"}),
        "The planks are smooth and polished.\n");
        
    add_item(({"racks"}),
        "The racks are tall and stocked with standard drow weapons.\n");
        
    add_item(({"weapons"}),
        "Scimitars, throwing spiders, daggers and rapiers hang neatly in " +
        "the weapons rack.\n");
    
    add_exit(CAMP_DIR + "camp1", "out");
}