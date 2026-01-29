#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f30",
        "southwest" : "r02/f28",
        "south" : "r02/f29",
        "northwest" : "r04/f28",
        "east" : "r03/f30",
        "north" : "r04/f29",
        "northeast" : "r04/f30",
        "west" : "r03/f28",
    ]));
    
}
