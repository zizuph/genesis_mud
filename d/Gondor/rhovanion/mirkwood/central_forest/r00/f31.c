#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r25",
        "south" : MIRKWOOD_OLDROAD_DIR + "r26",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r27",
        
        "northwest" : "r01/f30",
        "east" : "r00/f32",
        "north" : "r01/f31",
        "northeast" : "r01/f32",
        "west" : "r00/f30",
    ]));
    
}
