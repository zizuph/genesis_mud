#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["village": ({1, "southwest"}),
               "harbour": ({4, "south"})]);
    road = ({"north","southwest"});

    create_plain();

    add_exit(PLAINS + "plains_16_6", "north");
    add_exit(PLAINS + "plains_17_6", "northeast");
    add_exit(PLAINS + "plains_17_7", "east");
    add_exit(PLAINS + "plains_17_8", "southeast");
    add_exit(PLAINS + "plains_16_8", "south");
    add_exit(PLAINS + "plains_15_8", "southwest");
    add_exit(PLAINS + "plains_15_7", "west");
    add_exit(PLAINS + "plains_15_6", "northwest");
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