#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r43/f30",
        "southwest" : "r43/f28",
        "south" : "r43/f29",
        "northwest" : "r41/f28",
        "east" : "r42/f30",
        "north" : "r41/f29",
        "northeast" : "r41/f30",
        "west" : "r42/f28",
    ]));
    
}
