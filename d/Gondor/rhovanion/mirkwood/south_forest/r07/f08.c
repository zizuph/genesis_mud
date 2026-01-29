#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r08/f09",
        "southwest" : "r08/f07",
        "south" : "r08/p08-r08",
        "northwest" : "r06/f07",
        "east" : "r07/p09-r07",
        "north" : "r06/f08",
        "northeast" : "r06/p09-r06",
        "west" : "r07/f07",
    ]));
    
}
