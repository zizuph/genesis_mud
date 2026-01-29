#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public void
create_khalakhor_room()
{
    proxim = (["forest": ({0, "northeast"})]);
    road = ({"north","southeast"});
    mountains_hidden = 1;

    create_plain();

    add_exit(PLAINS + "plains_14_2", "southeast");
    add_exit(PLAINS + "plains_13_2", "south");
    add_exit(PLAINS + "plains_12_2", "southwest");
    add_exit(PLAINS + "plains_12_1", "west");
    add_fail("north", "A barricade has been erected to try and " +
        "deal with some poachers, it should come down " +
        "as soon as the problem is rectified.\n");
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