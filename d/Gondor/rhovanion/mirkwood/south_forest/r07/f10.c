#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r08/f11",
        "southwest" : "r08/f09",
        "south" : "r08/f10",
        "northwest" : "r06/p09-r06",
        "east" : "r07/f11",
        "north" : "r06/f10",
        "northeast" : "r06/f11",
        "west" : "r07/p09-r07",
    ]));
    
}
