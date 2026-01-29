#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(18);
    add_mirkwood_exits(([
        "southeast" : "r20/f29",
        "southwest" : "r20/f27",
        "south" : "r20/f28",
        "northwest" : "r19/f27",
        "east" : "r20/f29",
        "north" : "r19/f28",
        "northeast" : "r19/f29",
        "west" : "r20/f27",
    ]));
    
}
