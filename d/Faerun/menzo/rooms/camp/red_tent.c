/*
 * Clyptas - July 2017
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
    
    set_short ("Inside a large extravagant tent.");

    set_long("This tent is ornately decorated. Rich colors greet your " +
         "eyes upon entering. There is a large makeshift desk in the tent, " +
         "along with an empty rack that appears to be used for hanging " +
         "items.\n");
    
    add_item(({"desk","table"}),
        "There is a large ornately carved table that stands in the center " +
        "of the tent. Giving you the idea that whoever resides here is in " +
        "charge.\n");
    
    add_item(({"floor"}),
        "The floor of the tent is clean. Wood planks are laid out to keep " +
        "the area clean and the sweet smell of cedar from the planks fills " +
        "your nostrils.\n");
    
    add_item(({"planks"}),
        "The planks are smooth and polished.\n");
        
    add_item(({"carvings"}),
        "The carvivngs on the table show many creatures entwined in an eternal " +
        "battle.\n");
        
    add_item(({"rack"}),
        "The rack is empty, but it looks like it would hold clothes.\n");
    
    add_exit(CAMP_DIR + "camp1", "out");
}