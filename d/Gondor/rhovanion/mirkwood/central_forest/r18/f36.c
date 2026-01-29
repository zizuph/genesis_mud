#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r17/f37",
        "southwest" : "r17/f35",
        "south" : "r17/f36",
        "northwest" : "r19/f35",
        "east" : "r18/f37",
        "north" : "r19/f36",
        "northeast" : "r19/f37",
        "west" : "r18/f35",
    ]));
    
}
