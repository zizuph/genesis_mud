#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(54);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r08/f07",
        "southwest" : "r08/f05",
        "south" : "r08/f06",
        "northwest" : "r10/f05",
        "east" : "r09/f07",
        "north" : "r10/f06",
        "northeast" : "r10/f07",
        "west" : "r09/f05",
    ]));
    
}
