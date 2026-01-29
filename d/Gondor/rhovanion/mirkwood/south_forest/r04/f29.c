#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f30",
        "southwest" : "r05/f28",
        "south" : "r05/f29",
        "northwest" : "r03/f28",
        "east" : "r04/f30",
        "north" : "r03/f29",
        "northeast" : "r03/f30",
        "west" : "r04/f28",
    ]));
    
}
