#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r08/f49",
        "south" : "r08/f50",
        "northwest" : "r06/f49",
        "north" : "r06/f50",
        "west" : "r07/f49",
    ]));
    
}
