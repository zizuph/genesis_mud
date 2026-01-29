#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r36",
        "south" : MIRKWOOD_OLDROAD_DIR + "r37",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r38",
        
        "northwest" : "r01/f41",
        "east" : "r00/f43",
        "north" : "r01/f42",
        "northeast" : "r01/f43",
        "west" : "r00/f41",
    ]));
    
}
