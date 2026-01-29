#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r25/f30",
        "south" : "r25/f31",
        "northwest" : "r23/f30",
        "north" : "r23/f31",
        "west" : "r24/f30",
    ]));
    
}
