#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r28/f31",
        "southwest" : "r28/f29",
        "south" : "r28/f30",
        "northwest" : "r26/f29",
        "north" : "r26/f30",
        "west" : "r27/f29",
    ]));
    
}
