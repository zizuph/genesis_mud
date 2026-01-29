#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["river"  : ({2, "northwest"})]);
    road = ({"northwest", "southeast"});
    create_plain();

    add_exit(PLAINS + "plains_27_11", "north");
    add_exit(PLAINS + "plains_28_11", "northeast");
    add_exit(PLAINS + "plains_28_12", "east");
    add_exit(PLAINS + "plains_28_13", "southeast");
    add_exit(PLAINS + "plains_27_13", "south");
    add_exit(PLAINS + "plains_26_13", "southwest");
    add_exit(PLAINS + "plains_26_12", "west");
    add_exit(PLAINS + "plains_26_11", "northwest");
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
