#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r17/f25",
        "southwest" : "r17/f23",
        "south" : "r17/f24",
        "northwest" : "r19/f23",
        "east" : "r18/f25",
        "west" : "r18/f23",
    ]));
    
}
