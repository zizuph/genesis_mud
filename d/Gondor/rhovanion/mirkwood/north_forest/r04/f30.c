#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f31",
        "southwest" : "r03/f29",
        "south" : "r03/f30",
        "northwest" : "r05/f29",
        "east" : "r04/f31",
        "north" : "r05/f30",
        "northeast" : "r05/f31",
        "west" : "r04/f29",
    ]));
    
}
