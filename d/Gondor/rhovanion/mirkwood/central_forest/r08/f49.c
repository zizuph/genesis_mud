#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r07/f50",
        "southwest" : "r07/f48",
        "south" : "r07/f49",
        "northwest" : "r09/f48",
        "west" : "r08/f48",
    ]));
    
}
