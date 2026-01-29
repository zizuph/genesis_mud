#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f46",
        "southwest" : "r06/f44",
        "south" : "r06/f45",
        "northwest" : "r04/f44",
        "east" : "r05/f46",
        "north" : "r04/f45",
        "northeast" : "r04/f46",
        "west" : "r05/f44",
    ]));
    
}
