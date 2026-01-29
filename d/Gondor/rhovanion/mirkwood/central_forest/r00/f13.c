#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r07",
        "south" : MIRKWOOD_OLDROAD_DIR + "r08",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r09",
        
        "northwest" : "r01/f12",
        "east" : "r00/f14",
        "north" : "r01/f13",
        "northeast" : "r01/f14",
        "west" : "r00/f12",
    ]));
    
}
