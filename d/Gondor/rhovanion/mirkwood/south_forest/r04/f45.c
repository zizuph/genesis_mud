#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f46",
        "southwest" : "r05/f44",
        "south" : "r05/f45",
        "northwest" : "r03/f44",
        "east" : "r04/f46",
        "north" : "r03/f45",
        "northeast" : "r03/f46",
        "west" : "r04/f44",
    ]));
    
}
