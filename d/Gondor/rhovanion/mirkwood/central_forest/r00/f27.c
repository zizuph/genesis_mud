#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r21",
        "south" : MIRKWOOD_OLDROAD_DIR + "r22",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r23",
        
        "northwest" : "r01/f26",
        "east" : "r00/f28",
        "north" : "r01/f27",
        "northeast" : "r01/f28",
        "west" : "r00/f26",
    ]));
    
}
