#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    road = ({"southeast","northwest"});
    create_plain();

    add_exit(PLAINS + "plains_36_17", "north");
    add_exit(PLAINS + "plains_37_17", "northeast");
    add_exit(PLAINS + "plains_37_18", "east");
    add_exit(PLAINS + "plains_37_19", "southeast");
    add_exit(PLAINS + "plains_36_19", "south");
    add_exit(PLAINS + "plains_35_19", "southwest");
    add_exit(PLAINS + "plains_35_18", "west");
    add_exit(PLAINS + "plains_35_17", "northwest");
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
