#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r34/f24",
        "southwest" : "r34/f22",
        "south" : "r34/f23",
        "northwest" : "r32/f22",
        "east" : "r33/f24",
        "north" : "r32/f23",
        "northeast" : "r32/f24",
        "west" : "r33/f22",
    ]));
    
}
