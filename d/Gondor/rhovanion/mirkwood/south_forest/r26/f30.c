#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r27/f29",
        "south" : "r27/f30",
        "northwest" : "r25/f29",
        "north" : "r25/f30",
        "northeast" : "r25/f31",
        "west" : "r26/f29",
    ]));
    
}
