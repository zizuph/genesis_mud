#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r18/f31",
        "southwest" : "r18/f29",
        "south" : "r18/f30",
        "northwest" : "r16/f29",
        "east" : "r17/f31",
        "north" : "r16/f30",
        "northeast" : "r16/f31",
        "west" : "r17/f29",
    ]));
    
}
