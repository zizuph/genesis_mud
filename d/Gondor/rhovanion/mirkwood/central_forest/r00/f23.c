#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r17",
        "south" : MIRKWOOD_OLDROAD_DIR + "r18",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r19",
        
        "northwest" : "r01/f22",
        "east" : "r00/f24",
        "north" : "r01/f23",
        "northeast" : "r01/f24",
        "west" : "r00/f22",
    ]));
    
}
