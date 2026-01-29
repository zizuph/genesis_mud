#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f42",
        "southwest" : "r09/f40",
        "south" : "r09/f41",
        "northwest" : "r07/f40",
        "east" : "r08/f42",
        "north" : "r07/f41",
        "northeast" : "r07/f42",
        "west" : "r08/f40",
    ]));
    
}
