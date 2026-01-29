#include "../defs.h"

inherit MIRKWOOD_SPIDER_DIR + "base_treasure_chart";

public void
create_treasure_chart()
{
    set_short("beginner level treasure chart");
    
    add_treasure_for_type(TREASURE_MINOR_ITEM1, ({ 
        "/d/Gondor/common/obj/shovel",
        "/d/Gondor/common/obj/hammer",
        &create_money(0, 0, 0, 10)
    }));
}