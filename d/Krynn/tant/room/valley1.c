/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
#include <macros.h>
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("High above you is a road, perched on a ridge. The valley " +
        "stretches out in all east directions.\n");
    AI("road","The road follows a mountain path.\n");
    AI("ridge","The ridge appears to be climbable, and the best way to get " +
        "back to the road.\n");

    AE(TROOM + "valley4", "northeast", 0, 1);
    AE(TROOM + "valley5", "east", 0, 1);
    AE(TROOM + "valley6", "southeast", 0, 1);

    ACI(({"up","up ridge","up the ridge", "ridge"}),"climb","@@go_road");
    reset_tant_room();
}

go_road()
{
    write("You climb up the ridge back onto the road!\n");
    set_dircmd("up");
    TP->move_living("climbing up the ridge", TROOM + "road12", 0, 0);
    return "";
} 

