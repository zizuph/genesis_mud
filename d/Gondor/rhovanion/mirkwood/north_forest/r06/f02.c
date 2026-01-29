#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r05/f03",
        "southwest" : "r05/f01",
        "south" : "r05/f02",
        "northwest" : "r07/f01",
        "east" : "r06/f03",
        "north" : "r07/f02",
        "northeast" : "r07/f03",
        "west" : "r06/f01",
    ]));
    
}
