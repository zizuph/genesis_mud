#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r38/f37",
        "northwest" : "r36/f37",
        "north" : "r36/f38",
        "northeast" : "r36/f39",
        "west" : "r37/f37",
    ]));
    
}
