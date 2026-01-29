#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(75);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m30",
        "southwest" : "r06/m28",
        "south" : "r06/m29",
        "northwest" : "r08/f28",
        "east" : "r07/f30",
        "north" : "r08/f29",
        "northeast" : "r08/f30",
        "west" : "r07/f28",
    ]));
    
}
