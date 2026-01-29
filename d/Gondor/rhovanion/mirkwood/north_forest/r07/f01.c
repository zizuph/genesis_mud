#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r06/f02",
        "south" : "r06/f01",
        "east" : "r07/f02",
        "north" : "r08/f01",
        "northeast" : "r08/f02",
    ]));
    
}
