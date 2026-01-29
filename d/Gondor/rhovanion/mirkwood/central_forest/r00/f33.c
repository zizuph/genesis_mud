#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r27",
        "south" : MIRKWOOD_OLDROAD_DIR + "r28",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r29",
        
        "northwest" : "r01/f32",
        "east" : "r00/f34",
        "north" : "r01/f33",
        "northeast" : "r01/f34",
        "west" : "r00/f32",
    ]));
    
}
