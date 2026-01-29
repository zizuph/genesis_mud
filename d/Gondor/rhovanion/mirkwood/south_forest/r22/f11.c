#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r23/f12",
        "south" : "r23/f11",
        "northwest" : "r21/f10",
        "east" : "r22/f12",
        "north" : "r21/f11",
        "northeast" : "r21/f12",
    ]));
    
}
