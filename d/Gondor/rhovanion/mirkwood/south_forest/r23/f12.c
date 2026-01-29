#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r24/f13",
        "south" : "r24/f12",
        "northwest" : "r22/f11",
        "east" : "r23/f13",
        "north" : "r22/f12",
        "northeast" : "r22/f13",
        "west" : "r23/f11",
    ]));
    
}
