#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f10",
        "southwest" : "r02/f08",
        "south" : "r02/f09",
        "northwest" : "r04/f08",
        "east" : "r03/f10",
        "north" : "r04/f09",
        "northeast" : "r04/f10",
        "west" : "r03/f08",
    ]));
    
}
