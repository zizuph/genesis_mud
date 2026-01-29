#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["village": ({2, "west"}),
               "harbour": ({2, "south"})]);
    road = ({"southeast", "west"});
    create_plain();

    add_exit(PLAINS + "plains_18_8", "north");
    add_exit(PLAINS + "plains_19_9", "east");
    add_exit(PLAINS + "plains_19_10", "southeast");
    add_exit(PLAINS + "plains_18_10", "south");
    add_exit(PLAINS + "plains_17_10", "southwest");
    add_exit(PLAINS + "plains_17_9", "west");
    add_exit(PLAINS + "plains_17_8", "northwest");
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
