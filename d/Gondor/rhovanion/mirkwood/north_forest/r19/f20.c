#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r18/f21",
        "southwest" : "r18/f19",
        "south" : "r18/f20",
        "east" : "r19/f21",
        "west" : "r19/f19",
    ]));
    
}
