#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r07/p09-r07",
        "southwest" : "r07/f07",
        "south" : "r07/f08",
        "northwest" : "r05/f07",
        "east" : "r06/p09-r06",
        "north" : "r05/f08",
        "northeast" : "r05/p09-r05",
        "west" : "r06/f07",
    ]));
    
}
