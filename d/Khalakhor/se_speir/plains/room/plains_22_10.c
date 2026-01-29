#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["harbour" : ({1, "south"}),
               "river"   : ({1, "east"})]);
    extra = "Off to the east you can see a bridge " +
        "which spans the river. ";

    road = ({"east", "west"});
    create_plain();
    add_item("bridge", "The bridge is too distant to see any " +
        "detail.\n");

    add_exit(PLAINS + "plains_22_9", "north");
    add_exit(PLAINS + "plains_23_9", "northeast");
    add_exit(PLAINS + "plains_23_10", "east");
    add_exit(PLAINS + "plains_22_11", "south");
    add_exit(PLAINS + "plains_21_11", "southwest");
    add_exit(PLAINS + "plains_21_10", "west");
    add_exit(PLAINS + "plains_21_9", "northwest");
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
