#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r17/f38",
        "southwest" : "r17/f36",
        "south" : "r17/f37",
        "northwest" : "r19/f36",
        "east" : "r18/f38",
        "north" : "r19/f37",
        "west" : "r18/f36",
    ]));
    
}
