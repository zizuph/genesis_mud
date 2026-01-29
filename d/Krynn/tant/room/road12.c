/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
#include <macros.h>
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("A valley can be seen below you, as the road now " +
        "inclines sharply upwards, to Tantallon. The road continues " +
        "to the northwest and southwest.\n");
    AI("valley","The valley appears to be populated with wild creatures. " +
        "You could probably slide down a nearby ridge to get there.\n");
    AI(({"nearby ridge","ridge"}),"The ridge overlooks the valley below. " +
        "Sliding down the ridge would let you explore the valley.\n");
    AI("tantallon","You cannot see the mountain city of Tantallon from " +
        "this vantage point.\n");

    AE(TROOM + "road11", "southwest", 0, 2);
    AE(TROOM + "road13", "northwest", 0, 2);

    ACI(({"down","down ridge","down the ridge"}),"slide",
        "@@go_valley");
    reset_tant_room(); 
}

go_valley()
{
    write("You take a brief glance back, then slide down the ridge into " +
        "the valley below!\n\n\nWheeeeeee!!!\n\n\n\n");
    set_dircmd("down");
    TP->move_living("down the ridge",TROOM + "valley1", 0, 0);
    setuid();
    seteuid(getuid());
    write_file("/d/Krynn/tant/room/found_valley_log", ctime(time()) + ": " + 
               TP->query_name() + ".\n");
    return "";
}


