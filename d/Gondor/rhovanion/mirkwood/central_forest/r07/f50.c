#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r06/f51",
        "southwest" : "r06/f49",
        "south" : "r06/f50",
        "northwest" : "r08/f49",
        "west" : "r07/f49",
    ]));
    
}
