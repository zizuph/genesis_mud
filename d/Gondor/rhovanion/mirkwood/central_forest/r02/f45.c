#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f46",
        "southwest" : "r01/f44",
        "south" : "r01/f45",
        "northwest" : "r03/f44",
        "east" : "r02/f46",
        "north" : "r03/f45",
        "northeast" : "r03/f46",
        "west" : "r02/f44",
    ]));
    
}
