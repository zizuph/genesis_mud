#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r05/f49",
        "south" : "r05/f50",
        "northwest" : "r03/f49",
        "east" : "r04/f51",
        "north" : "r03/f50",
        "northeast" : "r03/f51",
        "west" : "r04/f49",
    ]));
    
}
