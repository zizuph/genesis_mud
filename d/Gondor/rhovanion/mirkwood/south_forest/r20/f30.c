#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r20/f31",
        "southwest" : "r20/f29",
        "south" : "r20/f30",
        "northwest" : "r19/f29",
        "east" : "r20/f31",
        "north" : "r19/f30",
        "northeast" : "r19/f31",
        "west" : "r20/f29",
    ]));
    
}
