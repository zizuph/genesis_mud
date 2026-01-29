#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r21/f43",
        "east" : "r22/f45",
        "north" : "r21/f44",
        "northeast" : "r21/f45",
        "west" : "r22/f43",
    ]));
    
}
