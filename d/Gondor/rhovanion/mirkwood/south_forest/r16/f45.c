#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r17/f44",
        "south" : "r17/f45",
        "northwest" : "r15/f44",
        "east" : "r16/f46",
        "north" : "r15/f45",
        "northeast" : "r15/f46",
        "west" : "r16/f44",
    ]));
    
}
