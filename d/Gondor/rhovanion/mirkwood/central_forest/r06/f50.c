#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r05/f51",
        "southwest" : "r05/f49",
        "south" : "r05/f50",
        "northwest" : "r07/f49",
        "east" : "r06/f51",
        "north" : "r07/f50",
        "west" : "r06/f49",
    ]));
    
}
