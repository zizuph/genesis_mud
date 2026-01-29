#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r14",
        "south" : MIRKWOOD_OLDROAD_DIR + "r15",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r16",
        
        "northwest" : "r01/f19",
        "east" : "r00/f21",
        "north" : "r01/f20",
        "northeast" : "r01/f21",
        "west" : "r00/f19",
    ]));
    
}
