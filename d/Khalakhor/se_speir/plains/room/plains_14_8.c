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
    extra = "To the south rises the earthen embankment " +
        "surrounding Port Macdunn. ";
    add_item(({"embankment", "earthen embankment"}),
        "The embankment forms a low wall around the " +
        "village, rather crudely made from hard packed " +
        "earth. It isn't much of a defense, but at " +
        "least would slow down a large attack.\n");

    create_plain();

    add_exit(PLAINS + "plains_14_7", "north");
    add_exit(PLAINS + "plains_15_7", "northeast");
    add_exit(PLAINS + "plains_15_8", "east");
    add_exit(PLAINS + "plains_13_8", "west");
    add_exit(PLAINS + "plains_13_7", "northwest");
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
