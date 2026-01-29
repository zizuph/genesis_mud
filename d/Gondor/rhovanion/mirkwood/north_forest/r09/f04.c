#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r08/f05",
        "southwest" : "r08/f03",
        "south" : "r08/f04",
        "northwest" : "r10/f03",
        "east" : "r09/f05",
        "north" : "r10/f04",
        "northeast" : "r10/f05",
        "west" : "r09/f03",
    ]));
    
}
