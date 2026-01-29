#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r33/f23",
        "southwest" : "r33/f21",
        "south" : "r33/f22",
        "northwest" : "r31/f21",
        "east" : "r32/f23",
        "north" : "r31/f22",
        "northeast" : "r31/f23",
        "west" : "r32/f21",
    ]));
    
}
