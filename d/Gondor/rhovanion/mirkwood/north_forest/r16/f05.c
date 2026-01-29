#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r15/f06",
        "southwest" : "r15/f04",
        "south" : "r15/f05",
        "east" : "r16/f06",
        "northeast" : "r17/f06",
        "west" : "r16/f04",
    ]));
    
}
