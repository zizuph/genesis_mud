#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r12",
        "north" : MIRKWOOD_OLDROAD_DIR + "r13",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r14",

        "southeast" : "r01/f19",
        "southwest" : "r01/f17",
        "south" : "r01/f18",
        "east" : "r00/f19",
        "west" : "r00/f17",
    ]));
    
}
