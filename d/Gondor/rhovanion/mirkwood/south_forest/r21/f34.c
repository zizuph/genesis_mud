#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r22/f35",
        "southwest" : "r22/f33",
        "south" : "r22/f34",
        "northwest" : "r20/f33",
        "east" : "r21/f35",
        "north" : "r20/f34",
        "northeast" : "r20/f35",
        "west" : "r21/f33",
    ]));
    
}
