#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r30/f34",
        "southwest" : "r30/f32",
        "south" : "r30/f33",
        "east" : "r29/f34",
        "west" : "r29/f32",
    ]));
    
}
