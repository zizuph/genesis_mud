#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r37",
        "north" : MIRKWOOD_OLDROAD_DIR + "r38",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r39",

        "southeast" : "r01/f44",
        "southwest" : "r01/f42",
        "south" : "r01/p43",
        "east" : "r00/f44",
        "west" : "r00/p42",
    ]));
    
}
