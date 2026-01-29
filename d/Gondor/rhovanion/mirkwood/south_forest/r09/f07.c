#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r10/p08-r10",
        "southwest" : "r10/f06",
        "south" : "r10/f07",
        "northwest" : "r08/f06",
        "east" : "r09/p08-r09",
        "north" : "r08/f07",
        "northeast" : "r08/p08-r08",
        "west" : "r09/f06",
    ]));
    
}
