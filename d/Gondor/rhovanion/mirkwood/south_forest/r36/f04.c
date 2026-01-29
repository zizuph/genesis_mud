#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r37/f05",
        "northwest" : "r35/f03",
        "east" : "r36/f05",
        "north" : "r35/f04",
        "northeast" : "r35/f05",
        "west" : "r36/f03",
    ]));
    
}
