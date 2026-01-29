#include "plains.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
inherit PLAINBASE;

public int
block_bridge()
{
    if (this_player()->query_wiz_level())
        return 0;
    write("The bridge has been barricaded due to " +
        "river activity on the other side of the " +
        "river.\n");
    return 1;
}

public void
create_khalakhor_room()
{
    proxim = (["harbour": ({1, "southwest"}),
               "river"  : ({0, "east"})]);
    extra = "The road climbs eastwards over a old stone " +
        "bridge which spans the river here. ";
    road = ({"east", "west"});
    create_plain();
    add_item(({"bridge","stone bridge", "old bridge",
        "old stone bridge"}), "The old stone bridge appears to " +
        "have been constructed many years ago. However, it still " +
        "looks sturdy.\n");

    add_exit(PLAINS + "plains_23_9", "north");
    add_exit(PLAINS + "plains_24_9","northeast");
    add_exit(PLAINS + "bridge", "east");
    add_exit(PLAINS + "plains_22_11", "southwest");
    add_exit(PLAINS + "plains_22_10", "west");
    add_exit(PLAINS + "plains_22_9", "northwest");
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
