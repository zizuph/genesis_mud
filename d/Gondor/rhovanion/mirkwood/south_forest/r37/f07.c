#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r38/f08",
        "south" : "r38/f07",
        "northwest" : "r36/f06",
        "east" : "r37/f08",
        "north" : "r36/f07",
        "northeast" : "r36/f08",
        "west" : "r37/f06",
    ]));
    
}
