#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r19/f10",
        "south" : "r19/f09",
        "northwest" : "r17/f08",
        "east" : "r18/f10",
        "north" : "r17/f09",
        "northeast" : "r17/f10",
    ]));
    
}
