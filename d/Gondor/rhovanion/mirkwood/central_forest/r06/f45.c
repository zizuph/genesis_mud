#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f46",
        "southwest" : "r05/f44",
        "south" : "r05/f45",
        "northwest" : "r07/f44",
        "east" : "r06/f46",
        "north" : "r07/f45",
        "northeast" : "r07/f46",
        "west" : "r06/f44",
    ]));
    
}
