#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r07/f35",
        "south" : "r07/f36",
        "northwest" : "r09/f35",
        "north" : "r09/f36",
        "west" : "r08/f35",
    ]));
    
}
