#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(84);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f42",
        "southwest" : "r04/f40",
        "south" : "r04/f41",
        "northwest" : "r06/m40",
        "east" : "r05/f42",
        "north" : "r06/m41",
        "northeast" : "r06/f42",
        "west" : "r05/m40",
    ]));
    
}
