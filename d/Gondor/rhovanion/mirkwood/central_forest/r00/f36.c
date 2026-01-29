#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r30",
        "south" : MIRKWOOD_OLDROAD_DIR + "r31",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r32",
        
        "northwest" : "r01/f35",
        "east" : "r00/f37",
        "north" : "r01/f36",
        "northeast" : "r01/f37",
        "west" : "r00/f35",
    ]));
    
}
