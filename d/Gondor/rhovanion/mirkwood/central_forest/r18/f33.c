#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r17/f34",
        "southwest" : "r17/f32",
        "south" : "r17/f33",
        "northwest" : "r19/f32",
        "east" : "r18/f34",
        "north" : "r19/f33",
        "northeast" : "r19/f34",
        "west" : "r18/f32",
    ]));
    
}
