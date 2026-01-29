#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["forest":({2, "northeast"})]);
    road = ({"southeast","northwest"});

    create_plain();

    add_exit(PLAINS + "plains_15_2", "north");
    add_exit(PLAINS + "plains_16_2", "northeast");
    add_exit(PLAINS + "plains_16_3", "east");
    add_exit(PLAINS + "plains_16_4", "southeast");
    add_exit(PLAINS + "plains_15_4", "south");
    add_exit(PLAINS + "plains_14_4", "southwest");
    add_exit(PLAINS + "plains_14_3", "west");
    add_exit(PLAINS + "plains_14_2", "northwest");
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