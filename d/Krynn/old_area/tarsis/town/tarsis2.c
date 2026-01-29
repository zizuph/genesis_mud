/* Gates of Tarsis */

#include "/d/Krynn/common/defs.h" 
#include "/d/Krynn/tarsis/local.h"   

inherit OUTROOM

public void
create_tarsis_room()
{
    set_short("Northern mainstreet of Tarsis.\n");
    set_long("You are now standing on northern mainstreet of Tarsis.\n");  

    
    add_exit(TOWN + "tarsis1", "north");
    add_exit(TOWN + "tarsis3", "south");
}


