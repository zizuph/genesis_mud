#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r36/f39",
        "south" : "r36/f40",
        "northwest" : "r34/f39",
        "east" : "r35/f41",
        "north" : "r34/f40",
        "northeast" : "r34/f41",
        "west" : "r35/f39",
    ]));
    
}
