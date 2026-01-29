#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(66);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r08/f08",
        "southwest" : "r08/f06",
        "south" : "r08/f07",
        "northwest" : "r10/f06",
        "east" : "r09/f08",
        "north" : "r10/f07",
        "northeast" : "r10/f08",
        "west" : "r09/f06",
    ]));
    
}
