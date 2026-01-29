#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r19/f46",
        "southwest" : "r19/f44",
        "south" : "r19/f45",
        "northwest" : "r17/f44",
        "north" : "r17/f45",
        "west" : "r18/f44",
    ]));
    
}
