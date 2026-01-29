#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r42/f22",
        "southwest" : "r42/f20",
        "south" : "r42/f21",
        "northwest" : "r40/f20",
        "east" : "r41/f22",
        "north" : "r40/f21",
        "northeast" : "r40/f22",
        "west" : "r41/f20",
    ]));
    
}
