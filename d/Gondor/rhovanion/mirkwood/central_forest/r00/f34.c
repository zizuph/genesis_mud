#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r28",
        "south" : MIRKWOOD_OLDROAD_DIR + "r29",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r30",
        
        "northwest" : "r01/f33",
        "east" : "r00/f35",
        "north" : "r01/f34",
        "northeast" : "r01/f35",
        "west" : "r00/f33",
    ]));
    
}
