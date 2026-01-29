#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(32);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f46",
        "southwest" : "r03/f44",
        "south" : "r03/f45",
        "northwest" : "r05/f44",
        "east" : "r04/f46",
        "north" : "r05/f45",
        "northeast" : "r05/f46",
        "west" : "r04/f44",
    ]));
    
}
