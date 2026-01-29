#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(70);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m29",
        "southwest" : "r06/m27",
        "south" : "r06/m28",
        "northwest" : "r08/f27",
        "east" : "r07/f29",
        "north" : "r08/f28",
        "northeast" : "r08/f29",
        "west" : "r07/m27",
    ]));
    
}
