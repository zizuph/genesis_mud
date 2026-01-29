#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f30",
        "southwest" : "r07/f28",
        "south" : "r07/f29",
        "northwest" : "r09/f28",
        "east" : "r08/f30",
        "north" : "r09/f29",
        "northeast" : "r09/f30",
        "west" : "r08/f28",
    ]));
    
}
