#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["forest":({0, "north"})]);
    road = ({"northwest","southeast"});
    mountains_hidden = 1;

    create_plain();

    add_exit(PLAINS + "plains_15_2", "east");
    add_exit(PLAINS + "plains_15_3", "southeast");
    add_exit(PLAINS + "plains_14_3", "south");
    add_exit(PLAINS + "plains_13_3", "southwest");
    add_exit(PLAINS + "plains_13_2", "west");
    add_exit(PLAINS + "plains_13_1", "northwest");
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