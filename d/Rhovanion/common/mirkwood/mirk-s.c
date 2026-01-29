#include "/d/Rhovanion/defs.h"
inherit MIRK_DIR+"mirkwood";
#include <stdproperties.h>

public void
create_map_room()
{
    set_short("On a grassy path");
    set_long("You are walking on a grassy path along the Forest river "+
	     "which flows from the Mirkwood forest towards the Long Lake "+
	     "called also Annen by elves.\n");

    add_item(({ "river", "water" }),
	"Swift and icy cold water runs quickly from the Mirkwood in west "+
	"towards the Long Lake in the east.\n ");

    add_prop(ROOM_I_LIGHT, 1);
    add_std_exits();
}

