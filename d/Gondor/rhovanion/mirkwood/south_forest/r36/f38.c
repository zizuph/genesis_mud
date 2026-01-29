#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r37/f37",
        "south" : "r37/f38",
        "northwest" : "r35/f37",
        "east" : "r36/f39",
        "north" : "r35/f38",
        "northeast" : "r35/f39",
        "west" : "r36/f37",
    ]));
    
}
