#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r43/f28",
        "southwest" : "r43/f26",
        "south" : "r43/f27",
        "northwest" : "r41/f26",
        "east" : "r42/f28",
        "north" : "r41/f27",
        "northeast" : "r41/f28",
        "west" : "r42/f26",
    ]));
    
}
