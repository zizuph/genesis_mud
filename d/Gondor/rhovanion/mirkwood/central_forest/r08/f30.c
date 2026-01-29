#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(64);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f31",
        "southwest" : "r07/f29",
        "south" : "r07/f30",
        "northwest" : "r09/f29",
        "east" : "r08/f31",
        "north" : "r09/f30",
        "northeast" : "r09/f31",
        "west" : "r08/f29",
    ]));
    
}
