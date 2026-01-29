#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r20/f45",
        "south" : "r20/f46",
        "northwest" : "r19/f45",
        "north" : "r19/f46",
        "west" : "r20/f45",
    ]));
    
}
