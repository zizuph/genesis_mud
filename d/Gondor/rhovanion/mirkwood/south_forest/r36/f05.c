#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r37/f06",
        "south" : "r37/f05",
        "northwest" : "r35/f04",
        "east" : "r36/f06",
        "north" : "r35/f05",
        "northeast" : "r35/f06",
        "west" : "r36/f04",
    ]));
    
}
