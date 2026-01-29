#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r27/f14",
        "south" : "r27/f13",
        "northwest" : "r25/f12",
        "east" : "r26/f14",
        "north" : "r25/f13",
        "northeast" : "r25/f14",
        "west" : "r26/f12",
    ]));
    
}
