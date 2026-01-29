#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r22/f12",
        "south" : "r22/f11",
        "northwest" : "r20/f10",
        "east" : "r21/f12",
        "north" : "r20/f11",
        "northeast" : "r20/f12",
        "west" : "r21/f10",
    ]));
    
}
