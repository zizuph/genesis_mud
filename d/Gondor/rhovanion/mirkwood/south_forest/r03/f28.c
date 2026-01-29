#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f29",
        "southwest" : "r04/f27",
        "south" : "r04/f28",
        "northwest" : "r02/f27",
        "east" : "r03/f29",
        "north" : "r02/f28",
        "northeast" : "r02/f29",
        "west" : "r03/f27",
    ]));
    
}
