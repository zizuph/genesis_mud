#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r26",
        "south" : MIRKWOOD_OLDROAD_DIR + "r27",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r28",
        
        "northwest" : "r01/f31",
        "east" : "r00/f33",
        "north" : "r01/f32",
        "northeast" : "r01/f33",
        "west" : "r00/f31",
    ]));
    
}
