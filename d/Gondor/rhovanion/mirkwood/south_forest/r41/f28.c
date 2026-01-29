#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r42/f29",
        "southwest" : "r42/f27",
        "south" : "r42/f28",
        "northwest" : "r40/f27",
        "east" : "r41/f29",
        "north" : "r40/f28",
        "northeast" : "r40/f29",
        "west" : "r41/f27",
    ]));
    
}
