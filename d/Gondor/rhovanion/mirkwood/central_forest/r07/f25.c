#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(81);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m26",
        "southwest" : "r06/f24",
        "south" : "r06/m25",
        "northwest" : "r08/f24",
        "east" : "r07/m26",
        "north" : "r08/f25",
        "northeast" : "r08/f25",
        "west" : "r07/f24",
    ]));
    
}
