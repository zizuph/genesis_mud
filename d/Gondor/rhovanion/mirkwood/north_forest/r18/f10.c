#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r17/f11",
        "southwest" : "r17/f09",
        "south" : "r17/f10",
        "east" : "r18/f11",
        "northeast" : "r18/f11",
        "west" : "r18/f09",
    ]));
    
}
