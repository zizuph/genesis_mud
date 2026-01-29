#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r08/f36",
        "southwest" : "r08/f34",
        "south" : "r08/f35",
        "northwest" : "r10/f34",
        "east" : "r09/f36",
        "north" : "r10/f35",
        "west" : "r09/f34",
    ]));
    
}
