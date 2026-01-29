#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r22/f23",
        "southwest" : "r22/f21",
        "south" : "r22/f22",
        "northwest" : "r20/f21",
        "east" : "r21/f23",
        "north" : "r20/f22",
        "northeast" : "r20/f23",
        "west" : "r21/f21",
    ]));
    
}
