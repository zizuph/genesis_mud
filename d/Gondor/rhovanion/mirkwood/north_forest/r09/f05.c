#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(48);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r08/f06",
        "southwest" : "r08/f04",
        "south" : "r08/f05",
        "northwest" : "r10/f04",
        "east" : "r09/f06",
        "north" : "r10/f05",
        "northeast" : "r10/f06",
        "west" : "r09/f04",
    ]));
    
}
