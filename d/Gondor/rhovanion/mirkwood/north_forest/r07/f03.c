#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r06/f04",
        "southwest" : "r06/f02",
        "south" : "r06/f03",
        "northwest" : "r08/f02",
        "east" : "r07/f04",
        "north" : "r08/f03",
        "northeast" : "r08/f04",
        "west" : "r07/f02",
    ]));
    
}
