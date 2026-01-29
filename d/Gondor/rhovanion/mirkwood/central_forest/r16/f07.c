#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r15/f08",
        "southwest" : "r15/f06",
        "south" : "r15/f07",
        "northwest" : "r17/f06",
        "east" : "r16/f08",
        "north" : "r17/f07",
        "northeast" : "r17/f08",
        "west" : "r16/f06",
    ]));
    
}
