#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r19/f30",
        "southwest" : "r19/f28",
        "south" : "r19/f29",
        "northwest" : "r17/f28",
        "east" : "r18/f30",
        "north" : "r17/f29",
        "northeast" : "r17/f30",
        "west" : "r18/f28",
    ]));
    
}
