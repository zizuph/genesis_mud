#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r36/f40",
        "northwest" : "r34/f40",
        "north" : "r34/f41",
        "northeast" : "r34/f42",
        "west" : "r35/f40",
    ]));
    
}
