#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f30",
        "southwest" : "r41/f28",
        "south" : "r41/f29",
        "northwest" : "r39/f28",
        "east" : "r40/f30",
        "north" : "r39/f29",
        "northeast" : "r39/f30",
        "west" : "r40/f28",
    ]));
    
}
