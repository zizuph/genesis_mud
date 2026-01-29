#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r09/p08-r09",
        "southwest" : "r09/f06",
        "south" : "r09/f07",
        "northwest" : "r07/f06",
        "east" : "r08/p08-r08",
        "north" : "r07/f07",
        "northeast" : "r07/f08",
        "west" : "r08/f06",
    ]));
    
}
