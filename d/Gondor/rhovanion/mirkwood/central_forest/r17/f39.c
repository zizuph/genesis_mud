#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r16/f40",
        "southwest" : "r16/f38",
        "south" : "r16/f39",
        "northwest" : "r18/f38",
        "west" : "r17/f38",
    ]));
    
}
