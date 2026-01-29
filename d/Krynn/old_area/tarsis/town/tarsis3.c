/* Gates of Tarsis */

#include "/d/Krynn/common/defs.h" 
#include "/d/Krynn/tarsis/local.h"   

inherit OUTROOM

public void
create_tarsis_room()
{
    set_short("Northern mainstreet of Tarsis.\n");
    set_long("This is the norhtern main street of tarsis. You can see that it " +
	"is very dirty here, and you can feel the smell of evil.\n");  

    
    add_exit(TOWN + "tarsis2", "north");
    add_exit(TOWN + "tarsis4", "south");
}


