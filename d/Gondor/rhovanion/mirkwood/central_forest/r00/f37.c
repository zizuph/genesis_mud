#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r31",
        "south" : MIRKWOOD_OLDROAD_DIR + "r32",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r33",
        
        "northwest" : "r01/f36",
        "east" : "r00/f38",
        "north" : "r01/f37",
        "northeast" : "r01/f38",
        "west" : "r00/f36",
    ]));
    
}
