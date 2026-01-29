#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r39/f11",
        "south" : "r39/f10",
        "northwest" : "r37/f09",
        "east" : "r38/f11",
        "north" : "r37/p10",
        "northeast" : "r37/p11",
        "west" : "r38/p09",
    ]));
    
}
