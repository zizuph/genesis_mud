#pragma strict_types
 
#include "/d/Gondor/defs.h"
#include "../mirk_defs.h"
inherit  "/d/Gondor/common/mirkwood/forest/mirkwood";
#include <stdproperties.h>

public void
create_map_room()
{
    set_short("Thranduil bridge");
    set_long("You are standing on the wooden bridge over the Forest river. "+
             "It goes straight towards the big sturdy gate that leads into "+
             "some cave. You notice some sign right next to the gate. "+
             "You seems to be able pass the mountain along the river to the "+
             "northwest but that way leads only to the dangerous Mirkwood "+
             "forest. The only relatively safe way out is south back to the "+
             "unused path.\n");

    add_item("sign", "You may be able to read it.\n");
    add_cmd_item("sign", "read", "  Welcome to the kingdom of Thranduil!\n");
    add_item("bridge", "This is old wooden bridge obviously build by elves "+
                "from Thranduil caves.\n");
    add_item(({"river","water"}), "Cold water of the forest river runs swiftly "+
               "under the bridge towards the east.\n");
    add_item("mountains", "There is only one way to pass them - to walk along "+
              "the river to northwest.\n");
    add_item("gate","This is a sturdy gate. A magical aura " +
                    "seems to penetrate it's surface. It would " +
                    "appear impossible to break it down or " +
                    "open it without the explicit permission of " +
                    "Thranduil himself, King of the Caverns.\n");

    add_std_exits();
    // add_exit(MIRK_DIR+"thranduil/cave1", "north", 0, 1);
    add_prop(ROOM_I_LIGHT, 1);
}

public int
block_enter()
{
    if (TP->query_spider()) return 1;  /*** block spiders out of here ***/
    return 0;
}

public int
query_map_fatigue()
{
    return 2;
}

