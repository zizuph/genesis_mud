#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["river"  : ({4, "northwest"})]);
    road = ({"east","west"});
    create_plain();

    add_exit(PLAINS + "plains_29_12", "north");
    add_exit(PLAINS + "plains_30_12", "northeast");
    add_exit(PLAINS + "plains_30_13", "east");
    add_exit(PLAINS + "plains_30_14", "southeast");
    add_exit(PLAINS + "plains_29_14", "south");
    add_exit(PLAINS + "plains_28_14", "southwest");
    add_exit(PLAINS + "plains_28_13", "west");
    add_exit(PLAINS + "plains_28_12", "northwest");
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
