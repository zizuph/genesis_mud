#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r34/f31",
        "southwest" : "r34/f29",
        "south" : "r34/f30",
        "northwest" : "r32/f29",
        "east" : "r33/f31",
        "north" : "r32/f30",
        "northeast" : "r32/f31",
        "west" : "r33/f29",
    ]));
    
}
