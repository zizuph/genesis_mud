#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f47",
        "southwest" : "r04/f45",
        "south" : "r04/f46",
        "northwest" : "r06/f45",
        "east" : "r05/f47",
        "north" : "r06/f46",
        "northeast" : "r06/f47",
        "west" : "r05/f45",
    ]));
    
}
