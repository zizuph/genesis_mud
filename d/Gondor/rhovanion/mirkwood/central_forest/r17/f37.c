#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r16/f38",
        "southwest" : "r16/f36",
        "south" : "r16/f37",
        "northwest" : "r18/f36",
        "east" : "r17/f38",
        "north" : "r18/f37",
        "northeast" : "r18/f38",
        "west" : "r17/f36",
    ]));
    
}
