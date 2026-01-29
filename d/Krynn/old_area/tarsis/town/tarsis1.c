#include "/d/Krynn/common/defs.h" 
#include "/d/Krynn/tarsis/local.h"   

inherit OUTROOM

public void
create_tarsis_room()
{
    set_short("inside gates of Tarsis.\n");
    set_long("You are now standing inside the mighty gate of Tarsis. To your right and left " +
	"you can see the old guard rooms. Once they must have looked beutiful but now they " +
	"are shattered. South the street continues deeper inside this now evil town.\n");  

    add_exit(TOWN + "guard1", "east");
    add_exit(TOWN + "guard2", "west");
    add_exit(TOWN + "gate1", "north");
    add_exit(TOWN + "tarsis2", "south");
}


