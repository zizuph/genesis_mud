#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r07/f11",
        "southwest" : "r07/p09-r07",
        "south" : "r07/f10",
        "northwest" : "r05/p09-r05",
        "east" : "r06/f11",
        "north" : "r05/f10",
        "northeast" : "r05/f11",
        "west" : "r06/p09-r06",
    ]));
    
}
