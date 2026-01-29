#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r17/f26",
        "southwest" : "r17/f24",
        "south" : "r17/f25",
        "east" : "r18/f26",
        "west" : "r18/f24",
    ]));
    
}
