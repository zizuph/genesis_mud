#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r42",
        "south" : MIRKWOOD_OLDROAD_DIR + "r43",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r44",
        
        "northwest" : "r01/f47",
        "east" : "r00/f49",
        "north" : "r01/f48",
        "northeast" : "r01/f49",
        "west" : "r00/f47",
    ]));
    
}
