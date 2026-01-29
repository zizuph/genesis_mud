#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r15",
        "south" : MIRKWOOD_OLDROAD_DIR + "r16",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r17",
        
        "northwest" : "r01/f20",
        "east" : "r00/f22",
        "north" : "r01/f21",
        "northeast" : "r01/f22",
        "west" : "r00/f20",
    ]));
    
}
