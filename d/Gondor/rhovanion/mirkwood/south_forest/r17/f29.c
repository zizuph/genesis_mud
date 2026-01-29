#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r18/f30",
        "southwest" : "r18/f28",
        "south" : "r18/f29",
        "northwest" : "r16/f28",
        "east" : "r17/f30",
        "north" : "r16/f29",
        "northeast" : "r16/f30",
        "west" : "r17/f28",
    ]));
    
}
