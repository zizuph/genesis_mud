#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f04",
        "southwest" : "r07/f02",
        "south" : "r07/f03",
        "northwest" : "r09/f02",
        "east" : "r08/f04",
        "north" : "r09/f03",
        "northeast" : "r09/f04",
        "west" : "r08/f02",
    ]));
    
}
