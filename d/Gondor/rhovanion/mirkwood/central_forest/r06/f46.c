#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f47",
        "southwest" : "r05/f45",
        "south" : "r05/f46",
        "northwest" : "r07/f45",
        "east" : "r06/f47",
        "north" : "r07/f46",
        "northeast" : "r07/f47",
        "west" : "r06/f45",
    ]));
    
}
