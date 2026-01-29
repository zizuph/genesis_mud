#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["village":({4, "southwest"}),
               "forest":({3, "north"})]);
    road = ({"southeast","northwest"});

    create_plain();

    add_exit(PLAINS + "plains_16_3", "north");
    add_exit(PLAINS + "plains_17_3", "northeast");
    add_exit(PLAINS + "plains_17_4", "east");
    add_exit(PLAINS + "plains_17_5", "southeast");
    add_exit(PLAINS + "plains_16_5", "south");
    add_exit(PLAINS + "plains_15_5", "southwest");
    add_exit(PLAINS + "plains_15_4", "west");
    add_exit(PLAINS + "plains_15_3", "northwest");
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