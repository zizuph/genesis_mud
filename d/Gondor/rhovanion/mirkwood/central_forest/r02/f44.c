#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f45",
        "southwest" : "r01/f43",
        "south" : "r01/f44",
        "northwest" : "r03/f43",
        "east" : "r02/f45",
        "north" : "r03/f44",
        "northeast" : "r03/f45",
        "west" : "r02/f43",
    ]));
    
}
