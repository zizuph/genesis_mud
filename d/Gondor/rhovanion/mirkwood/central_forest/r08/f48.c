#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r07/f49",
        "southwest" : "r07/f47",
        "south" : "r07/f48",
        "northwest" : "r09/f47",
        "east" : "r08/f49",
        "north" : "r09/f48",
        "west" : "r08/f47",
    ]));
    
}
