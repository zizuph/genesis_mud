#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r26/f29",
        "south" : "r26/f30",
        "northwest" : "r24/f29",
        "east" : "r25/f31",
        "north" : "r24/f30",
        "northeast" : "r24/f31",
        "west" : "r25/f29",
    ]));
    
}
