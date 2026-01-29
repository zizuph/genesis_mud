#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f29",
        "southwest" : "r02/f27",
        "south" : "r02/f28",
        "northwest" : "r04/f28",
        "east" : "r03/f29",
        "north" : "r04/f28",
        "northeast" : "r04/f29",
        "west" : "r03/f27",
    ]));
    
}
