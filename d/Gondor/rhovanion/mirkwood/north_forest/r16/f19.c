#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f20",
        "southwest" : "r15/f18",
        "south" : "r15/f19",
        "northwest" : "r17/f18",
        "east" : "r16/f20",
        "north" : "r17/f19",
        "northeast" : "r17/f20",
        "west" : "r16/f18",
    ]));
    
}
