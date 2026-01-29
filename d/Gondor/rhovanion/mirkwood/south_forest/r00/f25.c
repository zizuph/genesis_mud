#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r19",
        "north" : MIRKWOOD_OLDROAD_DIR + "r20",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r21",

        "southeast" : "r01/f26",
        "southwest" : "r01/f24",
        "south" : "r01/f25",
        "east" : "r00/f26",
        "west" : "r00/f24",
    ]));
    
}
