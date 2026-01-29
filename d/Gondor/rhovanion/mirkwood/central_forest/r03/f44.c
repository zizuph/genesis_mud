#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f45",
        "southwest" : "r02/f43",
        "south" : "r02/f44",
        "northwest" : "r04/f43",
        "east" : "r03/f45",
        "north" : "r04/f44",
        "northeast" : "r04/f45",
        "west" : "r03/f43",
    ]));
    
}
