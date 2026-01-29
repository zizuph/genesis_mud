#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r14",
        "north" : MIRKWOOD_OLDROAD_DIR + "r15",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r16",

        "southeast" : "r01/f21",
        "southwest" : "r01/f19",
        "south" : "r01/f20",
        "east" : "r00/f21",
        "west" : "r00/f19",
    ]));
    
}
