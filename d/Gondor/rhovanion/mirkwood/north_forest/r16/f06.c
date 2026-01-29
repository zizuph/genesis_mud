#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r15/f07",
        "southwest" : "r15/f05",
        "south" : "r15/f06",
        "east" : "r16/f07",
        "north" : "r17/f06",
        "northeast" : "r17/f07",
        "west" : "r16/f05",
    ]));
    
}
