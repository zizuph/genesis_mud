#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f25",
        "southwest" : "r41/f23",
        "south" : "r41/f24",
        "northwest" : "r39/f23",
        "east" : "r40/f25",
        "north" : "r39/f24",
        "northeast" : "r39/f25",
        "west" : "r40/f23",
    ]));
    
}
