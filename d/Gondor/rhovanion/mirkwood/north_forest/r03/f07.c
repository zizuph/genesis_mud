#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f08",
        "southwest" : "r02/f06",
        "south" : "r02/f07",
        "northwest" : "r04/f06",
        "east" : "r03/f08",
        "north" : "r04/f07",
        "northeast" : "r04/f08",
        "west" : "r03/f06",
    ]));
    
}
