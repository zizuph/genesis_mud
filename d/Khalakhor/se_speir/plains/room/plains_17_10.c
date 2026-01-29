#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>

inherit PLAINBASE;

public int
query_embankment_room()
{
    return 1;
}

public void
create_khalakhor_room()
{
    extra = "To the west rises the earthen embankment " +
        "that surrounds Port Macdunn. ";
    add_item(({"embankment", "earthen embankment"}),
        "The embankment forms a low wall around the " +
        "village, rather crudely made from hard packed " +
        "earth. It isn't much of a defense, but at " +
        "least would slow down a large attack.\n");
    proxim = (["harbour": ({1, "south"})]);

    create_plain();

    add_exit(PLAINS + "plains_17_9", "north");
    add_exit(PLAINS + "plains_18_9", "northeast");
    add_exit(PLAINS + "plains_18_10", "east");
    add_exit(PLAINS + "plains_18_11", "southeast");
    add_exit(PLAINS + "plains_17_11", "south");
}
int
do_lay(string str)
{

    if((str == "down") || (str == "grass") || (str == "heather"))
    {
	write("This close to the embankment isn't a good place "+
	  "to lay down so you change your mind.\n");
	say(QCTNAME(TP)+" examines the embankment carefully.\n");
	  
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
