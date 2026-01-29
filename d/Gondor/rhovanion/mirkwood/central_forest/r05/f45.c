#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f46",
        "southwest" : "r04/f44",
        "south" : "r04/f45",
        "northwest" : "r06/f44",
        "east" : "r05/f46",
        "north" : "r06/f45",
        "northeast" : "r06/f46",
        "west" : "r05/f44",
    ]));
    
}
