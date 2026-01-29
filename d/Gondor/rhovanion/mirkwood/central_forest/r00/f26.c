#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r20",
        "south" : MIRKWOOD_OLDROAD_DIR + "r21",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r22",
        
        "northwest" : "r01/f25",
        "east" : "r00/f27",
        "north" : "r01/f26",
        "northeast" : "r01/f27",
        "west" : "r00/f25",
    ]));
    
}
