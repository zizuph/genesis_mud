#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r41/f21",
        "southwest" : "r41/f19",
        "south" : "r41/f20",
        "northwest" : "r39/f19",
        "east" : "r40/f21",
        "north" : "r39/f20",
        "northeast" : "r39/f21",
        "west" : "r40/f19",
    ]));
    
}
