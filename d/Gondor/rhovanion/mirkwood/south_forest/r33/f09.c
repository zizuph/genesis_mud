#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r34/f10",
        "southwest" : "r34/f08",
        "south" : "r34/f09",
        "east" : "r33/f10",
        "north" : "r32/f09",
        "northeast" : "r32/f10",
        "west" : "r33/f08",
    ]));
    
}
