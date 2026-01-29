#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f09",
        "southwest" : "r02/f07",
        "south" : "r02/f08",
        "northwest" : "r04/f07",
        "east" : "r03/f09",
        "north" : "r04/f08",
        "northeast" : "r04/f09",
        "west" : "r03/f07",
    ]));
    
}
