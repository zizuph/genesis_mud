#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    extra = "The gates of Port Macdunn stand open to the " +
        "south. ";
    road = ({"northeast","south"});

    create_plain();

    add_exit(PLAINS + "plains_15_7", "north");
    add_exit(PLAINS + "plains_16_7", "northeast");
    add_exit(PLAINS + "plains_16_8", "east");
    add_exit("/d/Khalakhor/se_speir/port/room/road_12_1", "south");
    add_exit(PLAINS + "plains_14_8", "west");
    add_exit(PLAINS + "plains_14_7", "northwest");
}
int
do_lay(string str)
{

    if((str == "down") || (str == "grass") || (str == "heather"))
    {
	write("The road isn't a good place to lay down so you "+
	  "change your mind.\n");
	say(QCTNAME(TP)+" examines the road carefully.\n");
	  
    return 1;
    }
    else
   {
    notify_fail("Lay down?\n");
    return 0;
   }
}

void
init()
{
    ::init();

   add_action(do_lay, "lay");
}
