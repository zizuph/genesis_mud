#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r16/f30",
        "southwest" : "r16/f28",
        "south" : "r16/f29",
        "east" : "r17/f30",
        "west" : "r17/f28",
    ]));
    
}
