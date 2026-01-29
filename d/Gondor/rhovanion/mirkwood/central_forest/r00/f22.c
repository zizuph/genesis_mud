#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r16",
        "south" : MIRKWOOD_OLDROAD_DIR + "r17",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r18",
        
        "northwest" : "r01/f21",
        "east" : "r00/f23",
        "north" : "r01/f22",
        "northeast" : "r01/f23",
        "west" : "r00/f21",
    ]));
    
}
