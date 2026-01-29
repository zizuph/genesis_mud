#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(84);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f12",
        "southwest" : "r08/f10",
        "south" : "r08/f11",
        "northwest" : "r10/f10",
        "east" : "r09/f12",
        "north" : "r10/f11",
        "northeast" : "r10/f12",
        "west" : "r09/f10",
    ]));
    
}
