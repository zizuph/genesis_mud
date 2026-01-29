#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r35",
        "north" : MIRKWOOD_OLDROAD_DIR + "r36",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r37",

        "southeast" : "r01/f42",
        "southwest" : "r01/f40",
        "south" : "r01/f41",
        "east" : "r00/p42",
        "west" : "r00/f40",
    ]));
    
}
