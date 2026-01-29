#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r31/f40",
        "southwest" : "r31/f38",
        "south" : "r31/f39",
        "northwest" : "r29/f38",
        "east" : "r30/f40",
        "north" : "r29/f39",
        "west" : "r30/f38",
    ]));
    
}
