#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r34/f29",
        "southwest" : "r34/f27",
        "south" : "r34/f28",
        "northwest" : "r32/f27",
        "east" : "r33/f29",
        "north" : "r32/f28",
        "northeast" : "r32/f29",
        "west" : "r33/f27",
    ]));
    
}
