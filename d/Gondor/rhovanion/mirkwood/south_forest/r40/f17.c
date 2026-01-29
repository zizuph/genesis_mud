#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r41/f18",
        "south" : "r41/f17",
        "northwest" : "r39/f16",
        "east" : "r40/f18",
        "north" : "r39/f17",
        "northeast" : "r39/f18",
        "west" : "r40/f16",
    ]));
    
}
