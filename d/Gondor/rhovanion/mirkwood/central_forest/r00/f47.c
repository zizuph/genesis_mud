#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r41",
        "south" : MIRKWOOD_OLDROAD_DIR + "r42",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r43",
        
        "northwest" : "r01/f46",
        "east" : "r00/f48",
        "north" : "r01/f47",
        "northeast" : "r01/f48",
        "west" : "r00/f46",
    ]));
    
}
