#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([        
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r05",
        "south" : MIRKWOOD_OLDROAD_DIR + "r06",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r07",
        
        "northwest" : "r01/f10",
        "east" : "r00/f12",
        "north" : "r01/f11",
        "northeast" : "r01/f12",
        "west" : "r00/f10",
    ]));
    
}
