#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r19/f31",
        "southwest" : "r19/f29",
        "south" : "r19/f30",
        "northwest" : "r17/f29",
        "east" : "r18/f31",
        "north" : "r17/f30",
        "northeast" : "r17/f31",
        "west" : "r18/f29",
    ]));
    
}
