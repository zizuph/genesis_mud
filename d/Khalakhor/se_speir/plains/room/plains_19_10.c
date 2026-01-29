#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["village": ({2, "west"}),
               "river"  : ({4, "east"}),
               "harbour": ({1, "south"})]);
    road = ({"east", "northwest"});
    create_plain();

    add_exit(PLAINS + "plains_19_9", "north");
    add_exit(PLAINS + "plains_20_9", "northeast");
    add_exit(PLAINS + "plains_20_10", "east");
    add_exit(PLAINS + "plains_20_11", "southeast");
    add_exit(PLAINS + "plains_19_11", "south");
    add_exit(PLAINS + "plains_18_11", "southwest");
    add_exit(PLAINS + "plains_18_10", "west");
    add_exit(PLAINS + "plains_18_9", "northwest");
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
