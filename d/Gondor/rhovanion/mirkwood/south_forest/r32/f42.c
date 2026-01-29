#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r33/f43",
        "southwest" : "r33/f41",
        "south" : "r33/f42",
        "northwest" : "r31/f41",
        "east" : "r32/f43",
        "north" : "r31/f42",
        "northeast" : "r31/f43",
        "west" : "r32/f41",
    ]));
    
}
