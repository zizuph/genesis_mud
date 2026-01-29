#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r43/f26",
        "southwest" : "r43/f24",
        "south" : "r43/f25",
        "northwest" : "r41/f24",
        "east" : "r42/f26",
        "north" : "r41/f25",
        "northeast" : "r41/f26",
        "west" : "r42/f24",
    ]));
    
}
