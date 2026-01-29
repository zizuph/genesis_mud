#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r06/f37",
        "southwest" : "r06/f35",
        "south" : "r06/f36",
        "northwest" : "r08/f35",
        "north" : "r08/f36",
        "west" : "r07/f35",
    ]));
    
}
