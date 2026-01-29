#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    road = ({"southeast","west"});
    create_plain();

    add_exit(PLAINS + "plains_35_16", "north");
    add_exit(PLAINS + "plains_36_16", "northeast");
    add_exit(PLAINS + "plains_36_17", "east");
    add_exit(PLAINS + "plains_36_18", "southeast");
    add_exit(PLAINS + "plains_35_18", "south");
    add_exit(PLAINS + "plains_34_18", "southwest");
    add_exit(PLAINS + "plains_34_17", "west");
    add_exit(PLAINS + "plains_34_16", "northwest");
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
