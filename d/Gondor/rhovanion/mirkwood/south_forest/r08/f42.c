#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f43",
        "southwest" : "r09/f41",
        "south" : "r09/f42",
        "northwest" : "r07/f41",
        "east" : "r08/f43",
        "north" : "r07/f42",
        "northeast" : "r07/f43",
        "west" : "r08/f41",
    ]));
    
}
