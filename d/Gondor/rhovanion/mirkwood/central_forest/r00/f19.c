#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r13",
        "south" : MIRKWOOD_OLDROAD_DIR + "r14",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r15",
        
        "northwest" : "r01/f18",
        "east" : "r00/f20",
        "north" : "r01/f19",
        "northeast" : "r01/f20",
        "west" : "r00/f18",
    ]));
    
}
