#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r17/f24",
        "southwest" : "r17/f22",
        "south" : "r17/f23",
        "northwest" : "r19/f22",
        "east" : "r18/f24",
        "north" : "r19/f23",
        "west" : "r18/f22",
    ]));
    
}
