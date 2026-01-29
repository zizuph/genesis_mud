#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["village":({2, "southwest"}),
               "forest": ({4, "north"})]);
    road = ({"northeast","south"});

    create_plain();

    add_exit(PLAINS + "plains_16_5", "north");
    add_exit(PLAINS + "plains_17_5", "northeast");
    add_exit(PLAINS + "plains_17_6", "east");
    add_exit(PLAINS + "plains_17_7", "southeast");
    add_exit(PLAINS + "plains_16_7", "south");
    add_exit(PLAINS + "plains_15_7", "southwest");
    add_exit(PLAINS + "plains_15_6", "west");
    add_exit(PLAINS + "plains_15_5", "northwest");
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