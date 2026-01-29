#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r04",
        "south" : MIRKWOOD_OLDROAD_DIR + "r05",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r06",
        
        "northwest" : "r01/f09",
        "east" : "r00/f11",
        "north" : "r01/f10",
        "northeast" : "r01/f11",
        "west" : "r00/f09",
    ]));
    
}
