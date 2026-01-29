#pragma strict_types
 
#include "/d/Gondor/defs.h"
#include "../mirk_defs.h"
inherit  "/d/Gondor/common/mirkwood/forest/mirkwood";
#include <stdproperties.h>
#include <composite.h>

public void
create_map_room()
{
    set_short("Bridge over the Enchanted river");
    set_long("You are standing on the bridge through Enchanted "+
             "river. As you look down at gloomy water you remember "+
             "the tale about poor dwarf Bombur that once fell into this "+
             "river. Fortunately forest elves repaired this bridge "+
             "lately making this crossing relatively safe.\n");

    add_item(({ "river", "water" }),
        "River has dark and gloomy water and even you can sense some "+
        "evil emmiting from it as it slowly flows from south to north.\n");
 
    add_prop(ROOM_I_LIGHT, 0);
    add_prop("_room_i_no_me_sun", 1);
    add_std_exits();
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
 

