#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "plains.h"

inherit PLAINBASE;

public string
road_desc()
{
    object room = find_object(PLAINS + "plains_36_18");
    if (room && TP->query_prop(LIVE_O_LAST_ROOM) == room)
        return "The road you followed comes to a " +
            "gradual end here and disappears beneath the " +
            "thick grass covering the ground. ";
    return "A dirt road emerges from the grass here and " +
        "leads away to the northwest. ";
}

public void
create_khalakhor_room()
{
    road = ({"northwest"});
    extra = "@@road_desc@@";
    create_plain();

    add_exit(PLAINS + "plains_37_18", "north");
    add_exit(PLAINS + "plains_38_18", "northeast");
    add_exit(PLAINS + "plains_38_19", "east");
    add_exit(PLAINS + "plains_38_20", "southeast");
    add_exit(PLAINS + "plains_37_20", "south");
    add_exit(PLAINS + "plains_36_20", "southwest");
    add_exit(PLAINS + "plains_36_19", "west");
    add_exit(PLAINS + "plains_36_18", "northwest");
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
