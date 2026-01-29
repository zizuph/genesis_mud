#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f31",
        "southwest" : "r41/f29",
        "south" : "r41/f30",
        "northwest" : "r39/f29",
        "east" : "r40/f31",
        "north" : "r39/f30",
        "northeast" : "r39/f31",
        "west" : "r40/f29",
    ]));
    
}
