#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r33/f30",
        "southwest" : "r33/f28",
        "south" : "r33/f29",
        "northwest" : "r31/f28",
        "east" : "r32/f30",
        "north" : "r31/f29",
        "northeast" : "r31/f30",
        "west" : "r32/f28",
    ]));
    
}
