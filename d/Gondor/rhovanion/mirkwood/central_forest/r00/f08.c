#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r02",
        "south" : MIRKWOOD_OLDROAD_DIR + "r03",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r04",
        
        "northwest" : "r01/f07",
        "east" : "r00/f09",
        "north" : "r01/f08",
        "northeast" : "r01/f09",
        "west" : "r00/f07",
    ]));
    
}
