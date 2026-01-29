#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r32/f43",
        "southwest" : "r32/f41",
        "south" : "r32/f42",
        "northwest" : "r30/f41",
        "east" : "r31/f43",
        "west" : "r31/f41",
    ]));
    
}
