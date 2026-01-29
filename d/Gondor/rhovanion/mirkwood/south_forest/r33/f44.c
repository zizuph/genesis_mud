#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r34/f43",
        "south" : "r34/f44",
        "northwest" : "r32/f43",
        "east" : "r33/f45",
        "north" : "r32/f44",
        "northeast" : "r32/f45",
        "west" : "r33/f43",
    ]));
    
}
