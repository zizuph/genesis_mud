#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r20/f12",
        "southwest" : "r20/f10",
        "south" : "r20/f11",
        "northwest" : "r18/f10",
        "east" : "r19/f12",
        "north" : "r18/f11",
        "northeast" : "r18/f12",
        "west" : "r19/f10",
    ]));
    
}
