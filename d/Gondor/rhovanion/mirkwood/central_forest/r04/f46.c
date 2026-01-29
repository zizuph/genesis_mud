#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f47",
        "southwest" : "r03/f45",
        "south" : "r03/f46",
        "northwest" : "r05/f45",
        "east" : "r04/f47",
        "north" : "r05/f46",
        "northeast" : "r05/f47",
        "west" : "r04/f45",
    ]));
    
}
