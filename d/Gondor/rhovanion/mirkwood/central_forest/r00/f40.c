#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r34",
        "south" : MIRKWOOD_OLDROAD_DIR + "r35",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r36",
        
        "northwest" : "r01/f39",
        "east" : "r00/f41",
        "north" : "r01/f40",
        "northeast" : "r01/f41",
        "west" : "r00/f39",
    ]));
    
}
