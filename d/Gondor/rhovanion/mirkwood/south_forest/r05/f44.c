#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r06/f45",
        "southwest" : "r06/f43",
        "south" : "r06/f44",
        "northwest" : "r04/f43",
        "east" : "r05/f45",
        "north" : "r04/f44",
        "northeast" : "r04/f45",
        "west" : "r05/f43",
    ]));
    
}
