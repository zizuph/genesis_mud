#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f12",
        "southwest" : "r06/f10",
        "south" : "r06/f11",
        "northwest" : "r08/f10",
        "east" : "r07/f12",
        "north" : "r08/f11",
        "northeast" : "r08/f12",
        "west" : "r07/f10",
    ]));
    
}
