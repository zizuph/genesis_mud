#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r35/f40",
        "south" : "r35/f41",
        "northwest" : "r33/f40",
        "east" : "r34/f42",
        "north" : "r33/f41",
        "northeast" : "r33/f42",
        "west" : "r34/f40",
    ]));
    
}
