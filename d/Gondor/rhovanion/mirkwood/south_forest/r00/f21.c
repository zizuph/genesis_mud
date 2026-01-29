#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r15",
        "north" : MIRKWOOD_OLDROAD_DIR + "r16",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r17",

        "southeast" : "r01/f22",
        "southwest" : "r01/f20",
        "south" : "r01/f21",
        "east" : "r00/f22",
        "west" : "r00/f20",
    ]));
    
}
