#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f31",
        "southwest" : "r04/f29",
        "south" : "r04/f30",
        "northwest" : "r02/f29",
        "east" : "r03/f31",
        "north" : "r02/f30",
        "northeast" : "r02/f31",
        "west" : "r03/f29",
    ]));
    
}
