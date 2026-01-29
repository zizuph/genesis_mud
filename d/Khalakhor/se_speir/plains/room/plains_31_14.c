#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    road = ({"north", "southeast"});
    create_plain();

    add_exit(PLAINS + "plains_31_13", "north");
    add_exit(PLAINS + "plains_32_13", "northeast");
    add_exit(PLAINS + "plains_32_14", "east");
    add_exit(PLAINS + "plains_32_15", "southeast");
    add_exit(PLAINS + "plains_31_15", "south");
    add_exit(PLAINS + "plains_30_15", "southwest");
    add_exit(PLAINS + "plains_30_14", "west");
    add_exit(PLAINS + "plains_30_13", "northwest");
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
