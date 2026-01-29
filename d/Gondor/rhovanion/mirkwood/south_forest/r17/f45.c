#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r18/f44",
        "south" : "r18/f45",
        "northwest" : "r16/f44",
        "north" : "r16/f45",
        "northeast" : "r16/f46",
        "west" : "r17/f44",
    ]));
    
}
