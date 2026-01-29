#include "/d/Shire/old_forest/defs.h"
inherit OLD_FOR_DIR+"old_forest";
#include <stdproperties.h>
#include <composite.h>

public void
create_map_room()
{
    set_short("The gate.\n");
    set_long("Deep under the hedge, a cutting have been made. " +
      "It's walls are made of bricks, raising steadily until they form " +
      "an arch above the tunnel. In the tunnel is a gate of thick-set " +
                "iron bars.\n");

    add_item(({ "hedge" }),
        "The hedge is a well planted unpassable hedge between Buckland " +
        "and the Old Forest.\n");
    add_item(("gate"), "The gate is open and is made of thick-set iron bars.\n");
 
    add_prop(ROOM_I_LIGHT, 1);
    add_prop("_room_i_no_me_sun", 1);
    add_std_exits();
}

public int
block_enter()
{
    if (this_player()->query_spider()) return 1;  /*** block spiders out of here ***/
    return 0;
}

public int
query_map_fatigue()
{
    return 2;
}

