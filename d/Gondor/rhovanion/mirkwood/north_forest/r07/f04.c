#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f05",
        "southwest" : "r06/f03",
        "south" : "r06/f04",
        "northwest" : "r08/f03",
        "east" : "r07/f05",
        "north" : "r08/f04",
        "northeast" : "r08/f05",
        "west" : "r07/f03",
    ]));
    
}
