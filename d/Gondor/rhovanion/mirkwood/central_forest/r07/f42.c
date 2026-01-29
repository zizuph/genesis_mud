#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(55);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r06/f43",
        "southwest" : "r06/m41",
        "south" : "r06/f42",
        "northwest" : "r08/f41",
        "east" : "r07/f43",
        "north" : "r08/f42",
        "northeast" : "r08/f43",
        "west" : "r07/f41",
    ]));
    
}
