#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r06/f47",
        "southwest" : "r06/f45",
        "south" : "r06/f46",
        "northwest" : "r04/f45",
        "east" : "r05/f47",
        "north" : "r04/f46",
        "northeast" : "r04/f47",
        "west" : "r05/f45",
    ]));
    
}
