#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r33/f31",
        "southwest" : "r33/f29",
        "south" : "r33/f30",
        "northwest" : "r31/f29",
        "east" : "r32/f31",
        "north" : "r31/f30",
        "northeast" : "r31/f31",
        "west" : "r32/f29",
    ]));
    
}
