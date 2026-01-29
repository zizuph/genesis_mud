#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r21",
        "north" : MIRKWOOD_OLDROAD_DIR + "r22",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r23",

        "southeast" : "r01/f28",
        "southwest" : "r01/f26",
        "south" : "r01/f27",
        "east" : "r00/f28",
        "west" : "r00/f26",
    ]));
    
}
