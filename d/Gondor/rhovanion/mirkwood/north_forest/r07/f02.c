#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r06/f03",
        "southwest" : "r06/f01",
        "south" : "r06/f02",
        "northwest" : "r08/f01",
        "east" : "r07/f03",
        "north" : "r08/f02",
        "northeast" : "r08/f03",
        "west" : "r07/f01",
    ]));
    
}
