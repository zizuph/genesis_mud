#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(52);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m41",
        "southwest" : "r06/m39",
        "south" : "r06/m40",
        "northwest" : "r08/f39",
        "east" : "r07/f41",
        "north" : "r08/f40",
        "northeast" : "r08/f41",
        "west" : "r07/m39",
    ]));
    
}
