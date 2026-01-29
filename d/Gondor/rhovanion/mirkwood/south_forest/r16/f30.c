#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r17/f31",
        "southwest" : "r17/f29",
        "south" : "r17/f30",
        "northwest" : "r15/f29",
        "east" : "r16/f31",
        "north" : "r15/f30",
        "northeast" : "r15/f31",
        "west" : "r16/f29",
    ]));
    
}
