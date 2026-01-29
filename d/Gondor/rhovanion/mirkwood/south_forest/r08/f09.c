#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r09/f10",
        "southwest" : "r09/p08-r09",
        "south" : "r09/f09",
        "northwest" : "r07/f08",
        "east" : "r08/f10",
        "north" : "r07/p09-r07",
        "northeast" : "r07/f10",
        "west" : "r08/p08-r08",
    ]));
    
}
