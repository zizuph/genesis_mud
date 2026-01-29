#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r16/f29",
        "southwest" : "r16/f27",
        "south" : "r16/f28",
        "east" : "r17/f29",
        "west" : "r17/f27",
    ]));
    
}
