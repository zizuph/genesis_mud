#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r30/f38",
        "southwest" : "r30/f36",
        "south" : "r30/f37",
        "east" : "r29/f38",
        "west" : "r29/f36",
    ]));
    
}
