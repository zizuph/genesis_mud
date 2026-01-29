#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f07",
        "southwest" : "r02/f05",
        "south" : "r02/f06",
        "northwest" : "r04/f05",
        "east" : "r03/f07",
        "north" : "r04/f06",
        "northeast" : "r04/f07",
        "west" : "r03/f05",
    ]));
    
}
