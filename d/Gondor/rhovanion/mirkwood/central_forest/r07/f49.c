#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r06/f50",
        "southwest" : "r06/f48",
        "south" : "r06/f49",
        "northwest" : "r08/f48",
        "east" : "r07/f50",
        "north" : "r08/f49",
        "west" : "r07/f48",
    ]));
    
}
