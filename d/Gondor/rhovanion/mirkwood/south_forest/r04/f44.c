#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r05/f45",
        "southwest" : "r05/f43",
        "south" : "r05/f44",
        "northwest" : "r03/f43",
        "east" : "r04/f45",
        "north" : "r03/f44",
        "northeast" : "r03/f45",
        "west" : "r04/f43",
    ]));
    
}
