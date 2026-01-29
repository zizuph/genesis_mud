#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r19",
        "south" : MIRKWOOD_OLDROAD_DIR + "r20",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r21",
        
        "northwest" : "r01/f24",
        "east" : "r00/f26",
        "north" : "r01/f25",
        "northeast" : "r01/f26",
        "west" : "r00/f24",
    ]));
    
}
