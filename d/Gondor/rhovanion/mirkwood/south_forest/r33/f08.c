#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r34/f09",
        "southwest" : "r34/f07",
        "south" : "r34/f08",
        "east" : "r33/f09",
        "northeast" : "r32/f09",
        "west" : "r33/f07",
    ]));
    
}
