#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["river"  : ({0, "northwest"})]);
    road = ({"northwest","southeast"});
    extra = "A bridge crosses the Sora not far " +
        "to the northwest. ";
    create_plain();

    add_exit(PLAINS + "plains_26_10", "north");
    add_exit(PLAINS + "plains_27_10", "northeast");
    add_exit(PLAINS + "plains_27_11", "east");
    add_exit(PLAINS + "plains_27_12", "southeast");
    add_exit(PLAINS + "plains_26_12", "south");
    add_exit(PLAINS + "plains_25_12", "southwest");
    add_exit(PLAINS + "plains_25_11", "west");
    add_exit(PLAINS + "plains_25_10", "northwest");
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
