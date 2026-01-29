#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r22/f42",
        "southwest" : "r22/f40",
        "south" : "r22/f41",
        "northwest" : "r20/f40",
        "east" : "r21/f42",
        "north" : "r20/f41",
        "northeast" : "r20/f42",
        "west" : "r21/f40",
    ]));
    
}
