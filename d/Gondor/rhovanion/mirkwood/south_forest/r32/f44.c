#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r33/f45",
        "southwest" : "r33/f43",
        "south" : "r33/f44",
        "northwest" : "r31/f43",
        "east" : "r32/f45",
        "west" : "r32/f43",
    ]));
    
}
