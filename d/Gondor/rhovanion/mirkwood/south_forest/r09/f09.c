#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r10/f10",
        "southwest" : "r10/p08-r10",
        "south" : "r10/f09",
        "northwest" : "r08/p08-r08",
        "east" : "r09/f10",
        "north" : "r08/f09",
        "northeast" : "r08/f10",
        "west" : "r09/p08-r09",
    ]));
    
}
