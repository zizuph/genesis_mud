#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r25/f13",
        "south" : "r25/f12",
        "northwest" : "r23/f11",
        "east" : "r24/f13",
        "north" : "r23/f12",
        "northeast" : "r23/f13",
    ]));
    
}
