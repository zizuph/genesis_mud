#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f09",
        "southwest" : "r03/f07",
        "south" : "r03/f08",
        "northwest" : "r05/f07",
        "east" : "r04/f09",
        "north" : "r05/f08",
        "northeast" : "r05/f09",
        "west" : "r04/f07",
    ]));
    
}
