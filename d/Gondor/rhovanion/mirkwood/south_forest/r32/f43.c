#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r33/f44",
        "southwest" : "r33/f42",
        "south" : "r33/f43",
        "northwest" : "r31/f42",
        "east" : "r32/f44",
        "north" : "r31/f43",
        "west" : "r32/f42",
    ]));
    
}
