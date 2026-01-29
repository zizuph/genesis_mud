#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r18/f19",
        "southwest" : "r18/f17",
        "south" : "r18/f18",
        "east" : "r19/f19",
        "west" : "r19/f17",
    ]));
    
}
