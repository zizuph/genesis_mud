#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r29/f31",
        "southwest" : "r29/f29",
        "south" : "r29/f30",
        "northwest" : "r27/f29",
        "east" : "r28/f31",
        "north" : "r27/f30",
        "west" : "r28/f29",
    ]));
    
}
