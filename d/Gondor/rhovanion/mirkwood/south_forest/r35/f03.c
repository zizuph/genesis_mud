#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r36/f04",
        "south" : "r36/f03",
        "east" : "r35/f04",
        "northeast" : "r34/f04",
        "west" : "r35/f02",
    ]));
    
}
