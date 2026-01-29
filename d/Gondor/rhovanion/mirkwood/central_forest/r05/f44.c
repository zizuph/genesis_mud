#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f45",
        "southwest" : "r04/f43",
        "south" : "r04/f44",
        "northwest" : "r06/f43",
        "east" : "r05/f45",
        "north" : "r06/f44",
        "northeast" : "r06/f45",
        "west" : "r05/f43",
    ]));
    
}
