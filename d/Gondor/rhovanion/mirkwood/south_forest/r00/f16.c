#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r10",
        "north" : MIRKWOOD_OLDROAD_DIR + "r11",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r12",

        "southeast" : "r01/f17",
        "southwest" : "r01/f15",
        "south" : "r01/f16",
        "east" : "r00/f17",
        "west" : "r00/f15",
    ]));
    
}
