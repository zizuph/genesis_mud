#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r30/f15",
        "southwest" : "r30/f13",
        "south" : "r30/f14",
        "east" : "r29/f15",
        "west" : "r29/f13",
    ]));
    
}
