#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r18/f12",
        "southwest" : "r18/f10",
        "south" : "r18/f11",
        "northwest" : "r16/f10",
        "east" : "r17/f12",
        "north" : "r16/f11",
        "northeast" : "r16/f12",
        "west" : "r17/f10",
    ]));
    
}
