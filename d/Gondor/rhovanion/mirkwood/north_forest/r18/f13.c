#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r17/f14",
        "southwest" : "r18/f12",
        "south" : "r17/f13",
        "northwest" : "r19/f12",
        "east" : "r18/f14",
        "north" : "r19/f13",
        "northeast" : "r19/f14",
        "west" : "r18/f12",
    ]));
    
}
