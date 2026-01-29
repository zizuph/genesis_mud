#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f23",
        "southwest" : "r41/f21",
        "south" : "r41/f22",
        "northwest" : "r39/f21",
        "east" : "r40/f23",
        "north" : "r39/f22",
        "northeast" : "r39/f23",
        "west" : "r40/f21",
    ]));
    
}
