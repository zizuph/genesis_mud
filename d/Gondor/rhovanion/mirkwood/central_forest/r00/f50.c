#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r44",
        "south" : MIRKWOOD_OLDROAD_DIR + "r45",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r46",
        
        "northwest" : "r01/f49",
        "east" : "r00/f51",
        "north" : "r01/f50",
        "northeast" : "r01/f51",
        "west" : "r00/f49",
    ]));
    
}
