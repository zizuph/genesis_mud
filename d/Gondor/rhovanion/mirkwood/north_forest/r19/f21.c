#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r18/f22",
        "southwest" : "r18/f20",
        "south" : "r18/f21",
        "east" : "r19/f22",
        "west" : "r19/f20",
    ]));
    
}
