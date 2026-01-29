#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f29",
        "southwest" : "r07/f27",
        "south" : "r07/f28",
        "northwest" : "r05/f27",
        "east" : "r06/f29",
        "north" : "r05/f28",
        "northeast" : "r05/f29",
        "west" : "r06/f27",
    ]));
    
}
