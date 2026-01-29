/* Gates of Tarsis */

#include "/d/Krynn/common/defs.h" 
#include "/d/Krynn/tarsis/local.h"   

inherit OUTROOM

public void
create_tarsis_room()
{
    set_short("Northern mainstreet of Tarsis.\n");
    set_long("This is the norhtern main street of tarsis. You can see that it " +
	"is very dirty here, and you can feel the smell of evil. The street " +
	"splits up here and become a crossroad. To your east you can hear " +
	"every sound that you can think of when you are in a bar. To your " +
	"west there is a shop.\n");  

    
    
    add_exit(TOWN + "tarsis3", "north");
    add_exit(TOWN + "tarsis5", "south");
    add_exit(TOWN + "dracbar", "east");
    add_exit(TOWN + "shop", "west");
}


