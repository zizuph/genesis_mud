#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r20/f43",
        "southwest" : "r20/f41",
        "south" : "r20/f42",
        "northwest" : "r19/f41",
        "east" : "r20/f43",
        "north" : "r19/f42",
        "northeast" : "r19/f43",
        "west" : "r20/f41",
    ]));
    
}
